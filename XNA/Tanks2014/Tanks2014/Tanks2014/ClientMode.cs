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
        private string server = "127.0.0.1";
        private TcpClient client;
        private NetworkStream stream;
        private StreamReader sReader;
        private StreamWriter sWriter;

        private int gameId;
        private Map map;
        private NetworkTank playerTank;
        private List<NetworkTank> tanks; //TODO: map

        public ClientMode(TanksGame host, string initData) : base(host)
        {
            try
            {
                client = new TcpClient(server, port);
                stream = client.GetStream();
                sReader = new StreamReader(stream, Encoding.ASCII);
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
                tanks.Add(playerTank);
                map.addObject(playerTank);
                map.focus = playerTank;
                //send player data
                sWriter.WriteLine(gameId + " " + playerTank.ToString() + " 0");
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
                            break;
                        }
                        foreach(NetworkTank nt in tanks)
                        {
                            if(id == nt.id)
                            {
                                nt.deleted = false;
                                nt.update(line);
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

        public override void draw(GameTime gameTime, Spriter drawer)
        {
            if (established)
            {
                map.draw(gameTime, drawer);
            } else
            {
                System.Console.Out.WriteLine(message); //TODO: draw on screen
            }
        }
    }
}
