using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    class TestMode : Mode
    {
        int angle = 0;
        public TestMode(TanksGame host) : base(host)
        {
        }
        public override void Update(GameTime gameTime)
        {
            angle = (int)gameTime.TotalGameTime.TotalSeconds * 90;
        }
        public override void Draw(GameTime gameTime, Spriter drawer)
        {
            drawer.draw(16, 16, 32, 32, 0, 0, angle);
            drawer.draw(100, 100, 32, 32, 0, 128, angle);
        }
    }
}
