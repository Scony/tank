using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tanks2014
{
    public class DrawInfo
    {
        public DrawInfo(int sx, int sy, int sz)
        {
            spriteX = sx;
            spriteY = sy;
            size = sz;
        }
        public int spriteX;
        public int spriteY;
        public int size;
    }
}
