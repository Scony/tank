using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Tanks2014
{
    class NetworkPlayerTank : NetworkTank
    {
        public NetworkPlayerTank(string initData) : base(initData)
        {
            string playerData;
            try
            {
                playerData = System.IO.File.ReadAllText(@"config.txt");
            } catch (Exception)
            {
                playerData = "\nunknown\n\n255,255,255";
            }
            string[] lines = playerData.Split ('\n');
            string[] colors = lines [3].Split (',');

            int r = (int)Convert.ToDecimal(colors[0]);
            int g = (int)Convert.ToDecimal(colors[1]);
            int b = (int)Convert.ToDecimal(colors[2]);

            nick = lines[1];
            color = new Color(r,g,b);
        }

        public override void update(GameTime gameTime, Map map)
        {
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
                if(weapons [activeWeapon].shoot(x + 12, y + 12, rotation, map))
                {
                    switch(activeWeapon)
                    {
                        case 0:
                            shoot += 1;
                            break;
                        case 1:
                            shoot += 10000;
                            break;
                    }
                }
            }

            //tank move
            bool moving = true;
            if (state.IsKeyDown(Keys.Down))
            {
                y += speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.DOWN;
            } else if (state.IsKeyDown(Keys.Up))
            {
                y -= speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.UP;
            } else if (state.IsKeyDown(Keys.Left))
            {
                x -= speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.LEFT;
            } else if (state.IsKeyDown(Keys.Right))
            {
                x += speed * gameTime.ElapsedGameTime.TotalSeconds;
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

            if(fuel == 0)
            {
                rotation = realRotation;
                revert();
            }

            //caterpillar move
            if ((int)realX != (int)x || (int)realY != (int)y)
            {
                info.spriteX = 32 - info.spriteX;
            }
        }
    }
}
