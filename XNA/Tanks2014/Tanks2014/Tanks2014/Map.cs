using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    class Map
    {
        readonly int width;
        readonly int height;

        int screenW = 800;
        int screenH = 480;

        int camX = 0, camY = 0;

        MapObject[,] terrain;
        List<MapObject> objects;
        public MapObject center { set; get; }

        public Map(int w, int h)
        {
            height = h;
            width = w;
            terrain = new Terrain[w,h];
            for (int i = 0; i < w; i++)
            {
                for (int j = 0; j < h; j++)
                {
                    if((i+j)%10 == 0)
                        terrain[i, j] = new Bush().setXY(i*Size.MEDIUM, j*Size.MEDIUM);
                    else
                        terrain[i, j] = new Pavement().setXY(i * Size.MEDIUM, j * Size.MEDIUM);
                }
            }

            for (int i = 0; i < w; i++)
            {
                terrain[i, 0] = new Concrete().setXY(i * Size.MEDIUM, 0);
                terrain[i, h - 1] = new Concrete().setXY(i * Size.MEDIUM, (h - 1) * Size.MEDIUM);
            }
            for (int i = 0; i < h; i++)
            {
                terrain[0, i] = new Concrete().setXY(0, i * Size.MEDIUM);
                terrain[w - 1, i] = new Concrete().setXY((w - 1) * Size.MEDIUM, i * Size.MEDIUM);
            }
            objects = new List<MapObject>();
        }

        public void addObject(MapObject obj)
        {
            objects.Add(obj);
        }

        public void update(GameTime gameTime)
        {
            foreach(MapObject mo in objects){
                mo.update(gameTime);
            }
        }
        public void draw(GameTime gameTime, Spriter drawer)
        {
            camX = (int)center.x - screenW / 2;
            camY = (int)center.y - screenH / 2;
            
            if (camX > width * Size.MEDIUM - screenW) camX = width * Size.MEDIUM - screenW;
            if (camX < 0) camX = 0;
            if (camY > height * Size.MEDIUM - screenH) camY = height * Size.MEDIUM - screenH;
            if (camY < 0) camY = 0;

            List<MapObject> toDraw = new List<MapObject>();
            int offsetX = camX / Size.MEDIUM;
            int offsetY = camY / Size.MEDIUM;
            for(int i = offsetX < 0?-offsetX:0; i < screenW/Size.MEDIUM + 1 && offsetX + i < width; i++)
                for (int j = offsetY < 0 ? -offsetY : 0; j < screenH / Size.MEDIUM + 1 && offsetY + j < height; j++)
                {
                    MapObject mo = terrain[i + offsetX, j + offsetY];
                    if (mo != null)
                    {
                        toDraw.Add(mo);
                    }
                }
            foreach (MapObject mo in objects)
            {
                toDraw.Add(mo);
            }
            toDraw.Sort();
            foreach (MapObject mo in toDraw)
            {
                drawer.draw((int)mo.x-camX, (int)mo.y-camY, mo.getDrawInfo(), mo.rotation);
            }
        }
    }
}
