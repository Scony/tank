using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using System.Net.Sockets;
using System.IO;

namespace Tanks2014
{
    class ClientMode : Mode
    {
        private bool established = false;
        private string message = "";

        private Int32 port = 1338;
        private string server = System.IO.File.ReadAllText(@"server.dat");
        private TcpClient client;
        private NetworkStream stream;
        private StreamReader sReader;
        private StreamWriter sWriter;

        private int gameId;
        private Map map;
        Hud hud;
        private NetworkTank playerTank;
        private List<NetworkTank> tanks; //TODO: map

        public ClientMode(TanksGame host, string initData) : base(host)
        {
            try
            {
                client = new TcpClient(server, port);
                stream = client.GetStream();
                sReader = new StreamReader(stream, Encoding.Default);
                sWriter = new StreamWriter(stream, Encoding.ASCII)
                {
                    AutoFlush = true
                };

                //create map
                map = new Map(initData);
                //create player tank
                string[] lines = initData.Split('\n');
                string[] parts = lines[lines.Length-2].Trim().Split(" ".ToCharArray(),2);
                gameId = int.Parse(parts[0]);
                playerTank = new NetworkPlayerTank(parts[1]);
                tanks = new List<NetworkTank>();
                hud = new Hud(playerTank);
                tanks.Add(playerTank);
                map.addObject(playerTank);
                map.focus = playerTank;
                //send player data
                sWriter.Write(gameId + " " + playerTank.ToString() + " 0\n");
                //receive tank amount
                int tankCount = int.Parse(sReader.ReadLine().Trim().Split(' ')[1]);
                //add each tank if he is not playerTank
                for(int i = 0; i < tankCount; i++)
                {
                    string line = sReader.ReadLine();
                    if(int.Parse(line.Trim().Split(' ')[0]) != playerTank.id)
                    {
                        NetworkTank neu = new NetworkTank(line);
                        tanks.Add(neu);
                        map.addObject(neu);
                    }
                }
                established = true;
            } catch (Exception)
            {
                message = "Could not connect to server";
            }
        }

        public override void update(GameTime gameTime)
        {
            if (established)
            {                
                if(playerTank.deleted)
                {
                    established = false;
                    message = "Game over";
                }
                try
                {
                    foreach(NetworkTank nt in tanks)
                    {
                        nt.deleted = true;
                    }
                    sWriter.Write(gameId + " " + playerTank.ToString() + " 0\n"); //TODO: dies
                    int tankCount = int.Parse(sReader.ReadLine().Trim().Split(' ')[1]);
                    for(int i = 0; i < tankCount; i++)
                    {
                        string line = sReader.ReadLine();
                        int id = int.Parse(line.Trim().Split(' ')[0]);
                        if(id == playerTank.id)
                        {
                            playerTank.deleted = false;
                            continue;
                        }
                        foreach(NetworkTank nt in tanks)
                        {
                            if(id == nt.id)
                            {
                                nt.deleted = false;
                                nt.update(line,map);
                                break;
                            }
                        }
                    }
                } catch (Exception)
                {
                    established = false;
                    message = "Connection error";
                }
                map.update(gameTime);
            }
        }

        public override void draw(GameTime gameTime, Drawer drawer)
        {
            if (established)
            {
                map.draw(gameTime, drawer);
                hud.draw(drawer, gameTime, map.tanks);
            } else
            {                
                drawer.drawText(0,0,message);
            }
        }
    }
}
