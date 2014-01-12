using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class Mode
    {
        protected TanksGame host;
        public Mode(TanksGame host)
        {
            this.host = host;
        }
        public abstract void Update(GameTime gameTime);
        public abstract void Draw(GameTime gameTime, Spriter drawer);
    }
}
