using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Weapon
    {
		public abstract class Projectible : MapObject
		{
			protected double speed;
			protected double range;
			protected double traveled;
			protected Tank owner;
			public int hp = 1;
			public int dmg = 1;

			public Projectible(Tank tank, double x, double y, Rotation rot, double speed, double range){
				setXY(x,y);
				rotation = rot;
				owner = tank;
				this.speed = speed;
				this.range = range;
				this.traveled = 0;
			}

			public override void update (GameTime gameTime, Map map)
			{
				if (traveled > range) {
					map.removeObject(this);
				}
				if (rotation == Rotation.LEFT) {
					x -= speed * gameTime.ElapsedGameTime.TotalSeconds;
				}
				else if (rotation == Rotation.RIGHT) {
					x += speed * gameTime.ElapsedGameTime.TotalSeconds;
				}
				else if (rotation == Rotation.UP) {
					y -= speed * gameTime.ElapsedGameTime.TotalSeconds;
				}
				else if (rotation == Rotation.DOWN) {
					y += speed * gameTime.ElapsedGameTime.TotalSeconds;
				}
				traveled += speed * gameTime.ElapsedGameTime.TotalSeconds;
			}

			public override void handleCollision (MapObject other, Map map)
			{
				if (other.getTypeId () / 100 == 1) {
					Tank t = (Tank)other;
					t.hp -= dmg;
					if (t.hp <= 0) {
						t.respawn();
						owner.frags++;
						map.addObject(new Bang((int)x,(int)y,Size.LARGE));
					}else map.addObject(new Bang((int)x,(int)y,Size.MEDIUM));
					map.removeObject(this);
				}
				if (other.getTypeId () / 100 == 2) {
					Projectible p = (Projectible) other;
					p.hp -= dmg;
					if (p.hp <= 0) {
						map.removeObject(p);
					}
					map.removeObject (this);
					map.addObject(new Bang((int)x,(int)y,Size.MEDIUM));
				}
			}
		}

		public Weapon (Tank owner)
		{
			this.owner = owner;
		}
		protected Tank owner;
		public string name;
		public abstract bool shoot(double x, double y, Rotation rot, Map map);
		protected double reload = 0;
		public int ammo { get; set; }
		public void update(GameTime gameTime)
		{
			if(reload > 0) reload -= gameTime.ElapsedGameTime.TotalSeconds;
		}
    }
}