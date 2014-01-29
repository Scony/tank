using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Consumable : MapObject
    {
		protected double inactive = 0;
		protected double maxInactive = 20000.0;
        protected int amount;
        protected bool hidden = false;
        protected Color color = Color.White;
        protected double blink;
        protected double blinkMax = 500.0;
        protected const double speed = 1000.0;

        public Consumable(int amount)
        {
            this.amount = amount;
        }
	
		public override void handleCollision (MapObject other, Map map)
		{
			if (inactive == 0) {
				if (other.getTypeId () / 100 == 1) {
					Tank t = (Tank)other;
					extractTo (t);
				}
				inactive = maxInactive;
			}
		}

        public override void update (GameTime gameTime, Map map)
		{
			if (inactive > 0) {
				inactive -= speed * gameTime.ElapsedGameTime.TotalSeconds;
				hidden = true;
				if(inactive < 0) inactive = 0;
			} else {
				blink += speed * gameTime.ElapsedGameTime.TotalSeconds;
				if (blink > blinkMax) {
					hidden = !hidden;
					blink = blink - blinkMax;
				}
			}
        }
        
        public override int getTypeId()
        {
            return 300;//TODO
        }

        public abstract void extractTo(Tank tank);
    }
}
