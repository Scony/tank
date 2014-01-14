﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class MapObject : IComparable<MapObject>
    {
        public abstract int getTypeId();
        public abstract DrawInfo getDrawInfo();
        public Rotation rotation = 0;
        public double x = 0;
        public double y = 0;

        public MapObject setXY(double x, double y)
        {
            this.x = x;
            this.y = y;
            return this;
        }

        public abstract void update(GameTime gameTime, Map map);

        public int CompareTo(MapObject other)
        {
            if (other == null)
            {
                return 1;
            }
            if (getTypeId() == other.getTypeId())
            {
                return 0;
            }
            return getTypeId() < other.getTypeId() ? -1 : 1;
        }
    }
}
