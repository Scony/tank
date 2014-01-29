using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    abstract class Terrain : MapObject
    {
        public override void update(GameTime gameTime, Map map)
        {
            
        }
    }

    class Brick : Terrain
    {
        public override int getTypeId()
        {
            return 1;
        }
        private static DrawInfo info = new DrawInfo(0,256,Size.MEDIUM);

        public override DrawInfo getDrawInfo()
        {
            return info;
        }
    }
    class Concrete : Terrain
    {
        public override int getTypeId()
        {
            return 2;
        }
        private static DrawInfo info = new DrawInfo(0, 256 + 16, Size.MEDIUM);

        public override DrawInfo getDrawInfo()
        {
            return info;
        }
    }
    class Pavement : Terrain
    {
        public override int getTypeId()
        {
            return 3;
        }
        private static DrawInfo info = new DrawInfo(0, 256 + 32, Size.MEDIUM);

        public override DrawInfo getDrawInfo()
        {
            return info;
        }
    }
    class Bush : Terrain
    {
        public override int getTypeId()
        {
            return 1000;
        }
        private static DrawInfo info = new DrawInfo(0, 256 + 48, Size.MEDIUM);

        public override DrawInfo getDrawInfo()
        {
            return info;
        }
    }
    class Water : Terrain
    {
        public override int getTypeId()
        {
            return 5;
        }
        private static DrawInfo info = new DrawInfo(0, 256 + 64, Size.MEDIUM);

        public override DrawInfo getDrawInfo()
        {
            return info;
        }
    }
}
