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
            id = int.Parse(numbers[0]);
            x = int.Parse(numbers[1]) * Size.MEDIUM;
            y = int.Parse(numbers[2]) * Size.MEDIUM;
            rotation = (Rotation)int.Parse(numbers[3]);
            commit();
            shoot = int.Parse(numbers[4]);
            color = Color.DarkGreen;
        }

        public override string ToString()
        {
            return string.Format("{0} {1} {2} {3} {4}",id,realX,realY,(int)realRotation,shoot);
        }

        public override DrawInfo getDrawInfo()
        {
            return info;
        }

        public void update(string updateData)
        {
            //TODO:
        }

        public override void update(GameTime gameTime, Map map)
        {
        }
    }
}
