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
        private Int32 port = 1338;
        private string server = "127.0.0.1";
        private TcpClient client;
        private NetworkStream stream;
        private StreamReader sReader;

        private Map map;

        public ClientMode(TanksGame host, string initData) : base(host)
        {
            map = new Map(initData);//TODO: NetworkMap
            //TODO: do smth with dat focus RE: move that problem into NetworkMap
            MapObject chuj = new PlayerTank();
            chuj.setXY(0, 0);
            map.addObject(chuj);
            map.focus = chuj;
            //TODO: get map form param
            //TODO: establish connection
        }

        public override void update(GameTime gameTime)
        {
            //TODO: send player tank info
            //TODO: receive updates
            //TODO: map updates
        }

        public override void draw(GameTime gameTime, Spriter drawer)
        {
            map.draw(gameTime, drawer);
        }
    }
}
