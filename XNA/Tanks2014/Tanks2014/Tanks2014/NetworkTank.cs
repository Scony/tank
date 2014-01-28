using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Tanks2014
{
    class NetworkTank : Tank
    {
        public int id;
        public int shoot;
        protected DrawInfo info = new DrawInfo(0, 0, Size.LARGE);

        public NetworkTank(string initData)
        {
            string[] numbers = initData.Trim().Split(' ');
            id = int.Parse(numbers [0]);
            x = int.Parse(numbers [1]);
            y = int.Parse(numbers [2]);
            rotation = (Rotation)int.Parse(numbers [3]);
            commit();
            shoot = int.Parse(numbers [4]);
            color = Color.DarkGreen;
        }

        public override string ToString()
        {
            return string.Format("{0} {1} {2} {3} {4}", id, (int)Math.Round(realX), (int)Math.Round(realY), (int)realRotation, shoot);
        }

        public override DrawInfo getDrawInfo()
        {
            return info;
        }

        public void update(string updateData, Map map)
        {
            string[] numbers = updateData.Trim().Split(' ');
            x = int.Parse(numbers [1]);
            y = int.Parse(numbers [2]);
            rotation = (Rotation)int.Parse(numbers [3]);
            commit();

            int nShoot = int.Parse(numbers [4]);
            if (nShoot != shoot)
            {
                if (nShoot / 10000 > shoot / 10000)
                {
                    activeWeapon = 1;
                } else
                {
                    activeWeapon = 0;
                }
                if (weapons [activeWeapon].shoot(x + 12, y + 12, rotation, map))
                {
                    shoot = nShoot;
                }
            }
        }

        public override void update(GameTime gameTime, Map map)
        {
            weapons [activeWeapon].update(gameTime);
        }
    }
}
