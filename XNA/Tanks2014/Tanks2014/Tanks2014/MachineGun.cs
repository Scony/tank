using System;

namespace Tanks2014
{
    public class MachineGun : Weapon
    {
		new class Projectible : Weapon.Projectible
		{
			static DrawInfo info = new DrawInfo(280,16,Size.SMALL);
			public Projectible(Tank owner, double x, double y, Rotation rot) : base(owner, x,y,rot, 500, 500)
			{
				dmg = 5;
				hp = 5;
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
				map.addObject(new Projectible(owner, x,y,rot));
				reload = 0.08;
                return true;
			}
            return false;
		}
		public MachineGun (Tank owner) : base(owner)
		{	name = "Minigun";
			
			ammo = 100;
		}
    }
}

