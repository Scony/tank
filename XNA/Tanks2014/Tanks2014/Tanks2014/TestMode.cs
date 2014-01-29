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
            string playerData;
            try
            {
                playerData = System.IO.File.ReadAllText(@"config.txt");
            } catch (Exception)
            {
                playerData = "\nunknown\n\n255,255,255";
            }
			string[] lines = playerData.Split ('\n');
			string[] colors = lines [3].Split (',');

			int r = (int)Convert.ToDecimal(colors[0]);
			int g = (int)Convert.ToDecimal(colors[1]);
			int b = (int)Convert.ToDecimal(colors[2]);

			pt = new PlayerTank(lines[1], new Color(r,g,b));

            //map = new Map(100,100);
			string mapData = System.IO.File.ReadAllText(@"medium.map");




			map = new Map(mapData);
			hud = new Hud(pt);

			pt.m = map;

			pt.respawn();

			map.addObject(pt);
            map.addObject(new AITank(Size.MEDIUM * 11,Size.MEDIUM ,0));
			map.addObject(new AITank(Size.MEDIUM,11*Size.MEDIUM ,0));
            map.focus = pt;
        }

        public override void update(GameTime gameTime)
        {
            map.update(gameTime);
        }

        public override void draw(GameTime gameTime, Drawer drawer)
        {
            map.draw(gameTime, drawer);
			hud.draw(drawer, gameTime, map.tanks);
        }
    }
}
