using System;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
	public class Hud
	{
		public const int Width = 180;
		private PlayerTank tank;
		public Hud (PlayerTank tank)
		{
			this.tank = tank;
		}
		public void draw(Spriter drawer){
			drawer.drawRect(0,0,Hud.Width, drawer.getScreenHeight(), new Color(.1f,.1f,.1f));
			drawer.drawText(Size.LARGE,0,"AMMO " + tank.ammo);
			drawer.drawText(Size.LARGE,Size.MEDIUM,"LIFE " + tank.hp);
			drawer.drawText(Size.LARGE,2*Size.MEDIUM,"FUEL " + tank.fuel);
		}
	}
}

