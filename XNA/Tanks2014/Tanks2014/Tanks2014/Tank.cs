using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Tank : MapObject
    {
        public int hp = 100;
		public int fuel = 1000;

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

        public override MapObject commit()
        {
            if (realX != 0 && realY != 0)
            {
                fuel -= (int)((Math.Abs(realX - x) + Math.Abs(realY - y)));
                fuel = fuel < 0 ? 0 : fuel;
            }
            realRotation = rotation;
            realX = x;
            realY = y;
            return this;
        }

        public override void handleCollision(MapObject other, Map map)
        {
            if (other.getTypeId() == 100)
            {
                revert();
                other.revert();
            }
            if (other.getTypeId() == 200)
            {
                hp -= 50;
                if (hp <= 0)
                {
                    map.removeObject(this);
                }
                map.removeObject(other);
            }
            if (other.getTypeId() == 201)
            {
                hp -= 10;
                if (hp <= 0)
                {
                    map.removeObject(this);
                }
                map.removeObject(other);
            }
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
