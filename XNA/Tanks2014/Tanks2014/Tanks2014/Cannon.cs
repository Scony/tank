using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    class Cannon : Weapon
    {
		new class Projectible : Weapon.Projectible
		{
			static DrawInfo info = new DrawInfo(16,16,Size.SMALL);
			public Projectible(double x, double y, Rotation rot) : base(x,y,rot, 200, 500)
			{
			}
			public override int getTypeId ()
			{
				return 200;
			}
			public override DrawInfo getDrawInfo ()
			{
				return info;
			}
		}
		public override void shoot(double x, double y, Rotation rot, Map map)
		{
			if (reload <= 0 && ammo > 0) {
				ammo--;
				map.addObject(new Projectible(x,y,rot));
				reload = 0.5;
			}
		}
    }
}
