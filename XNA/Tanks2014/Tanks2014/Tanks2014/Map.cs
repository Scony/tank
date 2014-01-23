using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public class Map
    {
        readonly int width;
        readonly int height;

        MapObject[,] terrain;
        List<MapObject> objects;
		List<MapObject> toRemove;
        public MapObject focus { set; get; }

		public Map(string input)
        {
            string[] lines = input.Split('\n');
            width = int.Parse(lines [0].Trim().Split(' ') [0]);
            height = int.Parse(lines [0].Trim().Split(' ') [1]);

            terrain = new Terrain[width, height];
            for (int j = 0; j < height; j++)
            {
                string[] numbers = lines [j + 1].Trim().Split(' ');
                for (int i = 0; i < width; i++)
                {
                    switch (int.Parse(numbers [i]))
                    {
                        case 1:
                            terrain [i, j] = new Brick();
                            break;
                        case 2:
                            terrain [i, j] = new Concrete();
                            break;
                        case 3:
                            terrain [i, j] = new Pavement();
                            break;
                        case 4:
                            terrain [i, j] = new Bush();
                            break;
                        case 5:
                            terrain [i, j] = new Water();
                            break;
                        default:
                            terrain [i, j] = null;
                            break;
                    }
                    if (terrain [i, j] != null)
                    {
                        terrain [i, j].setXY(i * Size.MEDIUM, j * Size.MEDIUM);
                    }
                }
            }

            objects = new List<MapObject>();
            toRemove = new List<MapObject>();

            int consumables = int.Parse(lines [height + 1]);
            for (int i = 0; i < consumables; i++)
            {
                string[] numbers = lines [height + 2 + i].Trim().Split(' ');
                int a = int.Parse(numbers[0]);
                int b = int.Parse(numbers[1]);
                int kind = int.Parse(numbers[2]);
                int amount = int.Parse(numbers[3]);

                switch(kind)
                {
                    case 1:
                        Ammo ammo = new Ammo(amount);
                        ammo.setXY(a*Size.MEDIUM,b*Size.MEDIUM);
                        objects.Add(ammo);
                        break;
                    case 2:
                        Fuel fuel = new Fuel(amount);
                        fuel.setXY(a*Size.MEDIUM,b*Size.MEDIUM);
                        objects.Add(fuel);
                        break;
                }
            }
		}

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
			toRemove = new List<MapObject>();
        }

        public void addObject(MapObject obj)
        {
            objects.Add(obj);
        }

		public void removeObject(MapObject obj)
        {
            toRemove.Add(obj);
			obj.deleted = true;
        }

        public void update(GameTime gameTime)
        {
			for(int i=0; i<toRemove.Count; i++){
				objects.Remove(toRemove[i]);
			}
			for(int i=0; i<objects.Count; i++){
				if(!objects[i].deleted)
					objects[i].update(gameTime, this);
			}
        }

        public void draw (GameTime gameTime, Spriter drawer)
		{
			int mapW = width * Size.MEDIUM;
			int mapH = height * Size.MEDIUM;

			int screenW = drawer.getScreenWidth ();
			int screenH = drawer.getScreenHeight ();

			int centerX = (int)focus.x + focus.getDrawInfo ().size / 2;
			int centerY = (int)focus.y + focus.getDrawInfo ().size / 2;

			int offsetX = 0;
			int offsetY = 0;

			// X axis calculations
			offsetX = screenW / 2 - centerX;
			if (mapW <= screenW)
				offsetX = (screenW - mapW) / 2;
			else if (screenW / 2 > centerX)
				offsetX = 0;
			else if (screenW / 2 > mapW - centerX)
				offsetX = screenW - mapW;

			// Y axis calculations
			offsetY = screenH / 2 - centerY;
			if (mapH <= screenH)
				offsetY = (screenH - mapH) / 2;
			else if (screenH / 2 > centerY)
				offsetY = 0;
			else if (screenH / 2 > mapH - centerY)
				offsetY = screenH - mapH;

            List<MapObject> toDraw = new List<MapObject>();

			for(int i = (offsetX < 0 ? -offsetX : 0) / Size.MEDIUM; i < (offsetX < 0 ? -offsetX : 0) / Size.MEDIUM + screenW / Size.MEDIUM + 1; i++)
				for (int j = (offsetY < 0 ? -offsetY : 0) / Size.MEDIUM; j < (offsetY < 0 ? -offsetY : 0) / Size.MEDIUM + screenH / Size.MEDIUM + 1; j++)
                {
					if(i >= width || j >= height)
						break;
                    MapObject mo = terrain[i, j];
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
				mo.draw(drawer, gameTime, offsetX, offsetY);
                //drawer.draw((int)mo.x+offsetX, (int)mo.y+offsetY, mo.getDrawInfo(), mo.rotation);
            }

            Fog.draw(screenW, screenH, centerX - Size.SMALL + offsetX, centerY - Size.SMALL + offsetY, 8.2f, drawer);
        }
    }
}
