using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Tanks2014
{
    class PlayerTank : Tank
    {
        private double speed = 100;
        private DrawInfo info = new DrawInfo(0, 0, Size.LARGE);

        public PlayerTank()
        {
            rotation = Rotation.RIGHT;// && wyjebane;
        }

	public PlayerTank (int x, int y, int rotation)
	{
		this.x = x;
		this.y = y;
		//this.rotation = rotation;
	}

        public override DrawInfo getDrawInfo()
        {
            return info;
        }

        public override void update(GameTime gameTime, Map map)
        {
			weapons[activeWeapon].update(gameTime);

            int lastX = (int)x;
            int lastY = (int)y;

            KeyboardState state = Keyboard.GetState();

			if (state.IsKeyDown(Keys.D1))
            {
				activeWeapon = 0;
            }
			if (state.IsKeyDown(Keys.D2))
            {
				activeWeapon = 1;
            }

			if (state.IsKeyDown(Keys.Space))
            {
				weapons[activeWeapon].shoot(x+12,y+12,rotation,map);
            }

            if (state.IsKeyDown(Keys.Down))
            {
                y += speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.DOWN;
            }
            else if (state.IsKeyDown(Keys.Up))
            {
                y -= speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.UP;
            }
            else if (state.IsKeyDown(Keys.Left))
            {
                x -= speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.LEFT;
            }
            else if (state.IsKeyDown(Keys.Right))
            {
                x += speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.RIGHT;
            }
            if (lastX != (int)x || lastY != (int)y)
            {
                info.spriteX = 32 - info.spriteX;
            }
        }
    }
}
