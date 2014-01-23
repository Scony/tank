using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Consumable : MapObject
    {
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

        public override void update(GameTime gameTime, Map map)
        {
            blink += speed * gameTime.ElapsedGameTime.TotalSeconds;
            if (blink > blinkMax)
            {
                hidden = !hidden;
                blink = blink - blinkMax;
            }
        }
        
        public override int getTypeId()
        {
            return -1;//TODO
        }

        public abstract void extractTo(Tank tank);
    }
}
