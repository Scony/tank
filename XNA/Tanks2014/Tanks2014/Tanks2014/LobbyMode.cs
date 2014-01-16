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
            message = "Initializing network connection";
            try
            {
                client = new TcpClient(server, port);
                stream = client.GetStream();
                sReader = new StreamReader(stream, Encoding.ASCII);
                //TODO: put below close's somewhere
                //stream.Close ();
                //client.Close ();
            } catch (ArgumentNullException e)
            {
                Console.WriteLine("ArgumentNullException: {0}", e);
            } catch (SocketException e)
            {
                Console.WriteLine("SocketException: {0}", e);
            } catch (Exception e)
            {
                Console.WriteLine("ExceptionA: {0}", e);
            }
        }

        public override void update(GameTime gameTime)
        {
            try
            {
                if (sReader.Peek() >= 0)
                {
                    string x = sReader.ReadLine();
                    //TODO: analyze result and check if game is found
                    message = x;
                }
            } catch (Exception)
            {
                message = "Could not connect to server. Reconnecting...";
                //TODO: try reconnect
            }
        }

        public override void draw(GameTime gameTime, Spriter drawer)
        {
            Console.WriteLine("Received: " + message);
        }
    }
}
