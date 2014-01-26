using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Tanks2014
{
    class AITank : Tank
    {
        private DrawInfo info = new DrawInfo(0, 0, Size.LARGE);

        public AITank()
        {
            rotation = Rotation.RIGHT;
            color = Color.Red;
        }

        public AITank(int x, int y, int rotation)
        {
            this.realX = x;
            this.realY = y;
            this.rotation = (Rotation)rotation;
            color = Color.Red;
        }

        public override DrawInfo getDrawInfo()
        {
            return info;
        }

        public override void update(GameTime gameTime, Map map)
        {
            weapons [activeWeapon].update(gameTime);

            //tank move
            Random rnd = new Random();
            int op = rnd.Next(0,4);
            bool moving = true;
            if (op == 1)
            {
                y += speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.DOWN;
            } else if (op == 2)
            {
                y -= speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.UP;
            } else if (op == 3)
            {
                x -= speed * gameTime.ElapsedGameTime.TotalSeconds;
                rotation = Rotation.LEFT;
            } else if (op == 4)
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

            //caterpillar move
            if ((int)realX != (int)x || (int)realY != (int)y)
            {
                info.spriteX = 32 - info.spriteX;
            }
        }
    }
}
