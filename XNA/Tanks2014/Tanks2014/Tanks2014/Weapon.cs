using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Weapon
    {
		public abstract void shoot(double x, double y, Rotation rot, Map map);
		protected double reload = 0;

		public void update(GameTime gameTime)
		{
			if(reload > 0) reload -= gameTime.ElapsedGameTime.TotalSeconds;
		}
    }
}