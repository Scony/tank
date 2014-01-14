using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    class TestMode : Mode
    {
        PlayerTank chuj;
        Map mapa;
        public TestMode(TanksGame host) : base(host)
        {
            chuj = new PlayerTank();
            chuj.setXY(80, 80);
            mapa = new Map(100,100);
            mapa.addObject(chuj);
            mapa.focus = chuj;
        }
        public override void update(GameTime gameTime)
        {
            mapa.update(gameTime);
        }
        public override void draw(GameTime gameTime, Spriter drawer)
        {
            mapa.draw(gameTime, drawer);
        }
    }
}
