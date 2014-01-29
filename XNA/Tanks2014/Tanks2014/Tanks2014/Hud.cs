using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace Tanks2014
{
	public class Hud
	{
		double time = 0;
		int fps = 100;
		int frames = 0;
		public const int Width = 180;
		private Tank tank;
		public Hud (Tank tank)
		{
			this.tank = tank;
		}
		public void draw (Drawer drawer, GameTime gameTime, List<Tank> tanks)
		{
			drawer.drawRect (0, 0, Hud.Width, drawer.getScreenHeight (), new Color (.1f, .1f, .1f));
			drawer.drawText (0, 0, "" + tank.weaponName);
			drawer.drawText (0, Size.MEDIUM, "AMMO " + tank.ammo);
			drawer.drawText (0, 2 * Size.MEDIUM, "LIFE " + tank.hp);
			drawer.drawText (0, 3 * Size.MEDIUM, "FUEL " + tank.fuel);

			tanks.Sort (new scoreCmp ());
			drawer.drawText (0, 5 * Size.MEDIUM, "SCORE ");
			for (int i=0; i<tanks.Count; i++) {
				string text = tanks [i].nick + tanks [i].frags;
				drawer.drawText (0, (6 + i) * Size.MEDIUM, tanks [i].nick, tanks [i].color);
				drawer.drawText (8 * Size.MEDIUM, (6 + i) * Size.MEDIUM, "" + tanks [i].frags);
			}

			time += gameTime.ElapsedGameTime.TotalMilliseconds;
			frames ++;
			if (time > 1000) {
				fps = frames;
				time = 0;
				frames = 0;
			}
			drawer.drawText(0,15*Size.MEDIUM,"FPS " + fps);
		}

		public class scoreCmp : IComparer<Tank>{
			int IComparer<Tank>.Compare( Tank x, Tank y ){
				if(x.frags > y.frags) return -1;
				if(x.frags < y.frags) return 1;

				int str = StringComparer.Ordinal.Compare(x.nick,y.nick);
				if(str != 0) return str;
				if(x.color.PackedValue < y.color.PackedValue) return -1;
				if(x.color.PackedValue > y.color.PackedValue) return 1;
				return 0;
			}
		}
	}
}

