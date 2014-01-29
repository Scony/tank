using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public class Fuel : Consumable
    {
        private DrawInfo info = new DrawInfo(128, 360, Size.LARGE);

        public Fuel(int amount) : base(amount)
        {
        }

        public override void extractTo(Tank tank)
        {
			tank.fuel += amount;
        }

        public override int getTypeId()
        {
			return 301;
        }

        public override DrawInfo getDrawInfo()
        {
            if(hidden)
                info.spriteX = 160;
            else
                info.spriteX = 128;

            return info;
        }
    }
}
