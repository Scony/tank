using System;

namespace Tanks2014
{
    public class MachineGun : Weapon
    {
		new class Projectible : Weapon.Projectible
		{
			static DrawInfo info = new DrawInfo(280,16,Size.SMALL);
			public Projectible(double x, double y, Rotation rot) : base(x,y,rot, 500, 500)
			{
			}
			public override int getTypeId ()
			{
				return 201;
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
				map.addObject(new Projectible(x,y,rot));
				reload = 0.1;
                return true;
			}
            return false;
		}
    }
}

