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
		public override void shoot(double x, double y, Rotation rot, Map map)
		{
			if (reload <= 0 && ammo > 0) {
				ammo--;
				map.addObject(new Projectible(x,y,rot));
				reload = 0.1;
			}
		}
    }
}

