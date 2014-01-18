using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public class Fuel : Consumable
    {
        private DrawInfo info = new DrawInfo(0, 0, Size.LARGE);

        public override void extractTo(Tank tank)
        {
            //
        }

        public override int getTypeId()
        {
            return -1; //TODO
        }

        public override DrawInfo getDrawInfo()
        {
            return info;
        }
    }
}
