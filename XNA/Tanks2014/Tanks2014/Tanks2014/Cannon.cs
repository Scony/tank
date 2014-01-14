using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    class Cannon : Weapon
    {
		class Projectible : MapObject
		{
			static DrawInfo info = new DrawInfo(16,16,Size.SMALL);
			double speed = 500;

			public Projectible(double x, double y, Rotation rot){
				setXY(x,y);
				rotation = rot;
			}

			public override DrawInfo getDrawInfo ()
			{
				return info;
			}

			public override void update (GameTime gameTime, Map map)
			{
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
			}

			public override int getTypeId ()
			{
				return 200;
			}
		}

		public override void shoot(double x, double y, Rotation rot, Map map)
		{
			if (reload <= 0) {
				map.addObject(new Projectible(x,y,rot));
				reload = 2;
			}
		}
    }
}
