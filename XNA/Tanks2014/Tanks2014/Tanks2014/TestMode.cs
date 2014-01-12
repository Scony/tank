using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    class TestMode : Mode
    {
        int angle = 0;
        PlayerTank chuj;
        Map mapa;
        public TestMode(TanksGame host) : base(host)
        {
            chuj = new PlayerTank();
            chuj.setXY(80, 80);
            mapa = new Map(100,100);
            mapa.addObject(chuj);
            mapa.center = chuj;
        }
        public override void update(GameTime gameTime)
        {
            mapa.update(gameTime);
            //angle = (int)gameTime.TotalGameTime.TotalSeconds % 4;
            //chuj.update(gameTime);
        }
        public override void draw(GameTime gameTime, Spriter drawer)
        {
            mapa.draw(gameTime, drawer);
            //drawer.draw(0, 0, Size.LARGE, 0, 0, angle);
            //drawer.draw(0, 32, Size.LARGE, 0, 128, 4 - angle);
            //for (int i = 0; i < 256; i += 32)
            //{
            //    drawer.draw(i+16, i, new Bush().getDrawInfo());
            //    drawer.draw(i, i + 16, new Bush().getDrawInfo());
            //    drawer.draw(i, i, new Bush().getDrawInfo());
            //    drawer.draw(i + 16, i + 16, new Bush().getDrawInfo());
            //}
            //drawer.draw((int)chuj.x, (int)chuj.y, chuj.getDrawInfo(), chuj.rotation);
        }
    }
}
