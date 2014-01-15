using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using System.Net.Sockets;

namespace Tanks2014
{
    class LobbyMode : Mode
    {
        public LobbyMode (TanksGame host) : base(host)
		{
			try {
				Int32 port = 1337;
				string server = "127.0.0.1";
				TcpClient client = new TcpClient (server, port);
				NetworkStream stream = client.GetStream ();
				Byte[] data = new Byte[256];
				String responseData = String.Empty;
				Int32 bytes = stream.Read (data, 0, data.Length);
				responseData = System.Text.Encoding.ASCII.GetString (data, 0, bytes);
				Console.WriteLine ("Received: {0}", responseData);
				stream.Close ();
				client.Close ();
			} catch (ArgumentNullException e) {
				Console.WriteLine ("ArgumentNullException: {0}", e);
			} catch (SocketException e) {
				Console.WriteLine ("SocketException: {0}", e);
			} catch (Exception) {
			}
        }
        public override void update(GameTime gameTime)
        {
        }
        public override void draw(GameTime gameTime, Spriter drawer)
        {
        }
    }
}
