using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Tank : MapObject
    {
		public string nick;
		private Color _color;
		public Color color {
			get {
				return _color;
			}
			set {
				_color = value;
				int light = _color.R + _color.G + _color.B;
				if (light < 100) {
					_color.R += (byte)((100 - light) / 2);
					_color.G += (byte)((100 - light) / 2);
					_color.B += (byte)((100 - light) / 2);
				}
			}
		}

		public int frags = 0;

        public int hp = 100;
		public int fuel = 2000;

		protected int maxHp;
        protected int maxFuel;
        protected double speed = 100;
        public Weapon[] weapons = new Weapon[10];
		protected int activeWeapon = 0;



		public int ammo {
			get {
				return weapons[activeWeapon].ammo;
			}
		}
		public string weaponName {
			get {
				return weapons[activeWeapon].name;
			}
		}

        public Tank(string nick, Color color)
		{
			this.nick = nick;
			this.color = color;
            weapons[0] = new Cannon(this);
			weapons[1] = new MachineGun(this);
        }

		public Map m;

		public void respawn()
		{
			deleted = true;
			fuel = 2000;
			hp = 100;
			weapons [0] = new Cannon (this);
			weapons [1] = new MachineGun (this);

			Random r = new Random();
			do {
				x = r.Next(0,5) * 5 * Size.LARGE + Size.MEDIUM;
				y = r.Next(0,5) * 5 * Size.LARGE + Size.MEDIUM;
			}while(m.collidesWithObjects(this));
			realX = x;
			realY = y;
			deleted = false;
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

		public override void draw (Drawer drawer, GameTime gameTime, int offsetX, int offsetY)
		{
			drawer.draw((int)realX+offsetX, (int)realY+offsetY, getDrawInfo(), realRotation, color);
		}
        
        public override int getTypeId()
        {
            return 100;
        }
    }
}
