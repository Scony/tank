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

			public Projectible(double x, double y, Rotation rot, double speed, double range){
				setXY(x,y);
				rotation = rot;
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
		}
		public abstract void shoot(double x, double y, Rotation rot, Map map);
		protected double reload = 0;

		public void update(GameTime gameTime)
		{
			if(reload > 0) reload -= gameTime.ElapsedGameTime.TotalSeconds;
		}
    }
}