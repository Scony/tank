using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    class TestMode : Mode
    {
        PlayerTank pt;
        Map map;
		Hud hud;

        public TestMode(TanksGame host) : base(host)
        {
            pt = new PlayerTank();
            pt.setXY(48, 48);
            //map = new Map(100,100);
			string mapData = System.IO.File.ReadAllText(@"medium.map");
			map = new Map(mapData);
			hud = new Hud(pt);
			map.addObject(pt);
            map.addObject(new AITank(128,128,0));
            map.focus = pt;
        }

        public override void update(GameTime gameTime)
        {
            map.update(gameTime);
        }

        public override void draw(GameTime gameTime, Spriter drawer)
        {
            map.draw(gameTime, drawer);
			hud.draw(drawer);
        }
    }
}
