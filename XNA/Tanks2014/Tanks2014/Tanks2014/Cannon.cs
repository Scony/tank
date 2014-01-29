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
			public Projectible(Tank owner, double x, double y, Rotation rot) : base(owner, x,y,rot, 200, 500)
			{

				dmg = 50;
				hp = 25;
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
		public override bool shoot(double x, double y, Rotation rot, Map map)
		{
			if (reload <= 0 && ammo > 0) {
				ammo--;
                switch((int)rot)
                {
                    case 0:
                        y -= 20;
                        break;
                    case 1:
                        x += 20;
                        break;
                    case 2:
                        y += 20;
                        break;
                    case 3:
                        x -= 20;
                        break;
                }
				map.addObject(new Projectible(owner, x,y,rot));
				reload = 0.5;
                return true;
			}
            return false;
		}
		public Cannon (Tank owner) : base(owner)
		{
			name = "Cannon";
			ammo = 10;
		}
    }
}
