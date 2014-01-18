using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using System.Net.Sockets;
using System.IO;

namespace Tanks2014
{
    class LobbyMode : Mode
    {
        private Int32 port = 1337;
        private string server = "127.0.0.1";
        private TcpClient client;
        private NetworkStream stream;
        private StreamReader sReader;
        private string message;

        public LobbyMode(TanksGame host) : base(host)
        {
            initialize();
        }

        private void initialize()
        {
            message = "Initializing network connection";
            try
            {
                client = new TcpClient(server, port);
                stream = client.GetStream();
                sReader = new StreamReader(stream, Encoding.ASCII);
                //TODO: put below close's somewhere
                //stream.Close ();
                //client.Close ();
            } catch (Exception)
            {
                message = "Initialization failed";
            }
        }

        public override void update(GameTime gameTime)
        {
            try
            {
                if (stream.DataAvailable)
                {
                    string line = sReader.ReadLine();
                    int players = int.Parse(line.Trim().Split(' ')[0]);
                    int playersTotal = int.Parse(line.Trim().Split(' ')[1]);
                    if(players != playersTotal)
                    {
                        message = "Waiting for players (" + players + "/" + playersTotal + ")";
                    } else
                    {
                        string data = sReader.ReadToEnd();
                        stream.Close();
                        client.Close();
                        host.setMode(new ClientMode(host,data));
                    }
                }
            } catch (Exception)
            {
                message = "Could not connect to server. Reconnecting...";
                initialize();
            }
        }

        public override void draw(GameTime gameTime, Spriter drawer)
        {
            Console.WriteLine(message); //TODO: draw on screen instead
        }
    }
}
