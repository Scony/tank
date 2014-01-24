using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public abstract class MapObject : IComparable<MapObject>
    {
        protected Rotation rotation = 0;
        public double realX = 0; //TODO: zmienić na własności
        public double realY = 0;
        public double x = 0;
        public double y = 0;
		public bool deleted = false;

        public abstract int getTypeId();
        public abstract DrawInfo getDrawInfo();
        public abstract void update(GameTime gameTime, Map map);

        public MapObject setXY(double x, double y)
        {
            this.x = x;
            this.y = y;
            return this;
        }

        public MapObject commit()
        {
            realX = x;
            realY = y;
            return this;
        }

        public MapObject revert()
        {
            x = realX;
            y = realY;
            return this;
        }

		public virtual void draw(Spriter drawer, GameTime gameTime, int offsetX, int offsetY)
        {
			drawer.draw((int)realX+offsetX, (int)realY+offsetY, getDrawInfo(), rotation);
		}

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
