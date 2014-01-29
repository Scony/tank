using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Tanks2014
{
    class MenuMode : Mode
    {
        public MenuMode(TanksGame host) : base(host)
        {
        }

        public override void update(GameTime gameTime)
        {
            KeyboardState state = Keyboard.GetState();

            if (state.IsKeyDown(Keys.D1))
            {
                host.setMode(new TestMode(host));
                return;
            }
            if (state.IsKeyDown(Keys.D2))
            {
                host.setMode(new LobbyMode(host));
                return;
            }
            if (state.IsKeyDown(Keys.D3))
            {
                host.Exit();
            }
        }

        public override void draw(GameTime gameTime, Drawer drawer)
        {
			drawer.drawText(100,100,"1 Test mode");
			drawer.drawText(100,200,"2 Network mode");
			drawer.drawText(100,300,"3 Exit");
        }
    }
}
