using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tanks2014
{
    class Fog
    {
        public static void draw(int screenW, int screenH, int centerX, int centerY, float radius, Drawer drawer)
        {
            int offsetX = centerX % Size.MEDIUM;
            int offsetY = centerY % Size.MEDIUM;
            for(int i = -1; i < screenW/Size.MEDIUM + 1; i++)
                for (int j = -1; j < screenW / Size.MEDIUM + 1; j++)
                {
                    int x = i - centerX / Size.MEDIUM;
                    int y = j - centerY / Size.MEDIUM;
                    int center = (x * x + y * y > radius * radius) ? 1 : 0;
                    if(center == 1)
                    {
                        int diag1 = (x - 1) * (x - 1) + (y - 1) * (y - 1) > radius * radius ? 1 : 0;
                        int diag2 = (x + 1) * (x + 1) + (y - 1) * (y - 1) > radius * radius ? 1 : 0;
                        int diag3 = (x + 1) * (x + 1) + (y + 1) * (y + 1) > radius * radius ? 1 : 0;
                        int diag4 = (x - 1) * (x - 1) + (y + 1) * (y + 1) > radius * radius ? 1 : 0;
                        
                        int left = (x - 1) * (x - 1) + y * y > radius * radius ? 1:0;
                        int right = (x + 1) * (x + 1) + y * y > radius * radius ? 1 : 0;
                        int up = x * x + (y - 1) * (y - 1) > radius * radius ? 1 : 0;
                        int down = x * x + (y + 1) * (y + 1) > radius * radius ? 1 : 0;

                        if (left + right + up + down + diag1 + diag2 + diag3 + diag4 == 8)
                        {
                            drawer.draw(i * Size.MEDIUM + offsetX, j * Size.MEDIUM + offsetY, Size.MEDIUM, 256, 96, 0);
                        }
                        else if (left + right + up + down == 4)
                        {
                            int rotation = (diag1 == 0) ? 0 : (diag2 == 0) ? 1 : (diag4 == 0) ? 2 : 4;
                            drawer.draw(i * Size.MEDIUM + offsetX, j * Size.MEDIUM + offsetY, Size.MEDIUM, 256 + 32, 96, rotation);
                        }
                        else if (left + right + up + down == 3)
                        {
                            int rotation = (up == 0) ? 0 : (right == 0) ? 1 : (down == 0) ? 2 : 3;
                            drawer.draw(i * Size.MEDIUM + offsetX, j * Size.MEDIUM + offsetY, Size.MEDIUM, 256 + 16, 96, rotation);
                        }
                        else if (left + right + up + down == 2)
                        {
                            int rotation = (up == 0 && left == 0) ? 0 : (up == 0 && right == 0) ? 1 : (down == 0 && left == 0) ? 2 : 4;
                            drawer.draw(i * Size.MEDIUM + offsetX, j * Size.MEDIUM + offsetY, Size.MEDIUM, 256 + 48, 96, rotation);
                        }
                    }
                }
        }
    }
}
