using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Tank : MapObject
    {
        public int hp;
		public int fuel;

		protected int maxHp;
        protected int maxFuel;
        protected double speed = 100;
        protected Weapon[] weapons = new Weapon[10];
		protected int activeWeapon = 0;
		protected Color color = Color.White;

		public int ammo {
			get {
				return weapons[activeWeapon].ammo;
			}
		}

        public Tank()
        {
            weapons[0] = new Cannon();
			weapons[1] = new MachineGun();
        }

		public override void draw (Spriter drawer, GameTime gameTime, int offsetX, int offsetY)
		{
			drawer.draw((int)realX+offsetX, (int)realY+offsetY, getDrawInfo(), realRotation, color);
		}
        
        public override int getTypeId()
        {
            return 100;
        }
    }
}
