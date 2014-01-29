using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Tanks2014
{
    public class PlayerTank : Tank
    {
        private DrawInfo info = new DrawInfo(0, 0, Size.LARGE);

		private double resp = 1;

        public PlayerTank(string nick, Color color) : base(nick, color)
        {
            rotation = Rotation.RIGHT;
        }

        public PlayerTank(int x, int y, int rotation, string nick, Color color) : base(nick, color)
        {
            this.x = x;
            this.y = y;
            this.rotation = (Rotation)rotation;
        }

        public override DrawInfo getDrawInfo()
        {
            return info;
        }

        public override void update(GameTime gameTime, Map map)
        {
			resp -= gameTime.ElapsedGameTime.TotalSeconds;
            weapons [activeWeapon].update(gameTime);

            KeyboardState state = Keyboard.GetState();

            //weapon switching
            if (state.IsKeyDown(Keys.D1))
            {
                activeWeapon = 0;
            }
            if (state.IsKeyDown(Keys.D2))
            {
                activeWeapon = 1;
            }

			if (state.IsKeyDown(Keys.R))
            {
				if(resp <= 0){
					frags--;
					respawn();
					resp = 1;
				}
				return;
            }

            //color switching
            if (state.IsKeyDown(Keys.I))
            {
                color = Color.LightGreen;
            }
            if (state.IsKeyDown(Keys.O))
            {
                color = Color.LightBlue;
            }
            if (state.IsKeyDown(Keys.P))
            {
                color = Color.LightCoral;
            }

            //shoot
            if (state.IsKeyDown(Keys.Space))
            {
                weapons [activeWeapon].shoot(x + 12, y + 12, rotation, map);
            }

            //tank move
            bool moving = true;
			double realSpeed = fuel == 0 ? speed / 5 : speed;
            if (state.IsKeyDown(Keys.Down))
            {
                y += realSpeed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.DOWN;
            } else if (state.IsKeyDown(Keys.Up))
            {
                y -= realSpeed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.UP;
            } else if (state.IsKeyDown(Keys.Left))
            {
                x -= realSpeed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.LEFT;
            } else if (state.IsKeyDown(Keys.Right))
            {
                x += realSpeed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.RIGHT;
            } else
            {
                moving = false;
            }
            if (moving && realRotation != rotation && Math.Abs((int)realRotation - (int)rotation) != 2)
            {
                x = Math.Round(realX / Size.MEDIUM) * Size.MEDIUM;
                y = Math.Round(realY / Size.MEDIUM) * Size.MEDIUM;
            }

            //caterpillar move
            if ((int)realX != (int)x || (int)realY != (int)y)
            {
                info.spriteX = 32 - info.spriteX;
            }
        }
    }
}
