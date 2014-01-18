using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Consumable : MapObject
    {
        public override void update(GameTime gameTime, Map map)
        {

        }

        public abstract void extractTo(Tank tank);
    }
}
