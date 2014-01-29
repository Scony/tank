using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public class Ammo : Consumable
    {
        private DrawInfo info = new DrawInfo(128, 392, Size.LARGE);
		private int type;
        public Ammo(int amount, int type) : base(amount)
        {
			this.type = type;
        }

        public override void extractTo(Tank tank)
        {
			tank.weapons[type].ammo += amount;
        }

        public override int getTypeId()
        {
            return 302; //TODO
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
