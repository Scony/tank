using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public class Map
    {
        protected readonly int width;
        protected readonly int height;
        protected MapObject[,] terrain;
        protected List<MapObject> objects;
        protected List<MapObject> toRemove;
		public List<Tank> tanks;

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
                        terrain [i, j].setXY(i * Size.MEDIUM, j * Size.MEDIUM).commit();
                    }
                }
            }

            objects = new List<MapObject>();
            toRemove = new List<MapObject>();
			tanks = new List<Tank>();

            int consumables = int.Parse(lines [height + 1]);
            for (int i = 0; i < consumables; i++)
            {
                string[] numbers = lines [height + 2 + i].Trim().Split(' ');
                int a = int.Parse(numbers [0]);
                int b = int.Parse(numbers [1]);
                int kind = int.Parse(numbers [2]);
                int amount = int.Parse(numbers [3]);

                switch (kind)
                {
					case 0:
                    case 1:
                        Ammo ammo = new Ammo(amount,kind);
                        ammo.setXY(a * Size.MEDIUM, b * Size.MEDIUM).commit();
                        objects.Add(ammo);
                        break;
                    case 2:
                        Fuel fuel = new Fuel(amount);
                        fuel.setXY(a * Size.MEDIUM, b * Size.MEDIUM).commit();
                        objects.Add(fuel);
                        break;
                }
            }
        }

        public Map(int w, int h)
        {
            height = h;
            width = w;
            terrain = new Terrain[w, h];
            for (int i = 0; i < w; i++)
            {
                for (int j = 0; j < h; j++)
                {
                    if ((i + j) % 10 == 0)
                        terrain [i, j] = new Bush().setXY(i * Size.MEDIUM, j * Size.MEDIUM).commit();
                    else
                        terrain [i, j] = new Pavement().setXY(i * Size.MEDIUM, j * Size.MEDIUM).commit();
                }
            }

            for (int i = 0; i < w; i++)
            {
                terrain [i, 0] = new Concrete().setXY(i * Size.MEDIUM, 0).commit();
                terrain [i, h - 1] = new Concrete().setXY(i * Size.MEDIUM, (h - 1) * Size.MEDIUM).commit();
            }
            for (int i = 0; i < h; i++)
            {
                terrain [0, i] = new Concrete().setXY(0, i * Size.MEDIUM).commit();
                terrain [w - 1, i] = new Concrete().setXY((w - 1) * Size.MEDIUM, i * Size.MEDIUM).commit();
            }
            objects = new List<MapObject>();
            toRemove = new List<MapObject>();
        }

        public void addObject (MapObject obj)
		{
			objects.Add (obj);
			if (obj.getTypeId () / 100 == 1) {
				tanks.Add((Tank) obj);
				((Tank)obj).m = this;
			}
        }

        public void removeObject(MapObject obj)
        {
            toRemove.Add(obj);
            obj.deleted = true;
        }

        public virtual void update(GameTime gameTime)
        {
            for (int i=0; i<toRemove.Count; i++)
            {
                objects.Remove(toRemove [i]);
            }

            for (int i=0; i<objects.Count; i++)
            {
                if (!objects [i].deleted)
                {
                    objects [i].update(gameTime, this);
                }
            }

           for (int i=0; i<objects.Count; i++)
            {
                if (!objects [i].deleted)
                {
                    checkCollision(objects [i], i);
                }
            }

            foreach (MapObject mo in objects)
            {
                mo.commit();
            }
        }

        protected void checkCollision(MapObject obj, int idx)
        {
            checkTerrainCollision(obj);
            checkObjectsCollision(obj, idx);
        }

        protected void checkTerrainCollision(MapObject obj)
        {
            for(int i = (int)obj.x / Size.MEDIUM; i <= ((int)obj.x + obj.getDrawInfo().size - 1) / Size.MEDIUM; i++)
            {
                for(int j = (int)obj.y / Size.MEDIUM; j <= ((int)obj.y + obj.getDrawInfo().size - 1) / Size.MEDIUM; j++)
                {
					if(i >= width || i <0 || j >= height || j < 0){
						obj.revert();
						return;
					}
                    if(obj.getTypeId() == 100 && terrain[i,j] != null && (terrain[i,j].getTypeId() == 1 || terrain[i,j].getTypeId() == 2 || terrain[i,j].getTypeId() == 5))
                    {
                        obj.revert();
                        return;
                    }
                    if((obj.getTypeId() == 200 || obj.getTypeId() == 201) && terrain[i,j] != null && terrain[i,j].getTypeId() == 1)
                    {
                        obj.deleted = true;
                        toRemove.Add(obj);
                        if(obj.getTypeId() == 200){
							terrain[i,j] = null;
							addObject(new Bang((int)obj.x,(int)obj.y,Size.MEDIUM));
						}
						else
							addObject(new Bang((int)obj.x,(int)obj.y,Size.SMALL));
                    }
                    if((obj.getTypeId() == 200 || obj.getTypeId() == 201) && terrain[i,j] != null && terrain[i,j].getTypeId() == 2)
                    {
                        obj.deleted = true;
                        toRemove.Add(obj);
						addObject(new Bang((int)obj.x,(int)obj.y,Size.SMALL));
                        return;
                    }
                }
            }
        }

		public bool collidesWithObjects(MapObject obj)
        {
			if(obj.x > (width-2) * width) return true;
			if(obj.y > (width-2) * width) return true;
            for (int i = 0; i<objects.Count; i++)
            {
                if (collides(obj, objects[i]))
                {
					return true;
                }
            }
			return false;
        }

        protected void checkObjectsCollision(MapObject obj, int idx)
        {
            for (int i = idx+1; i<objects.Count; i++)
            {
                if (collides(obj, objects [i]))
                {
                    if (obj.collisionId > objects [i].collisionId)
                    {
                        obj.handleCollision(objects [i],this);
                    } else
                    {
                        objects [i].handleCollision(obj,this);
                    }
                    //obj.handleCollision(objects [i],this);
                    //objects [i].handleCollision(obj,this);
                }
            }
        }

        public bool collides(MapObject o1, MapObject o2)
        {
			if(o1.deleted && o2.deleted) return false;
            int x11 = (int)o1.x;
            int y11 = (int)o1.y;
            int x12 = (int)o1.x + (int)o1.getDrawInfo().size - 1;
            int y12 = (int)o1.y + (int)o1.getDrawInfo().size - 1;

            int x21 = (int)o2.x;
            int y21 = (int)o2.y;
            int x22 = (int)o2.x + (int)o2.getDrawInfo().size - 1;
            int y22 = (int)o2.y + (int)o2.getDrawInfo().size - 1;


            if ((x11 <= x21 && x21 <= x12 && y11 <= y21 && y21 <= y12) ||
                (x11 <= x21 && x21 <= x12 && y11 <= y22 && y22 <= y12) ||
                (x11 <= x22 && x22 <= x12 && y11 <= y22 && y22 <= y12) ||
                (x11 <= x22 && x22 <= x12 && y11 <= y21 && y21 <= y12))
                return true;

            return false;
        }

        public void draw(GameTime gameTime, Drawer drawer)
        {
            int mapW = width * Size.MEDIUM;
            int mapH = height * Size.MEDIUM;

			int screenW = drawer.getScreenWidth();
            int screenH = drawer.getScreenHeight();

            int centerX = (int)focus.realX + focus.getDrawInfo().size / 2;
            int centerY = (int)focus.realY + focus.getDrawInfo().size / 2;

            int offsetX = 0;
            int offsetY = 0;

            // X axis calculations
            offsetX = (screenW - Hud.Width)/ 2 - centerX + Hud.Width;
            if (mapW <= screenW - Hud.Width)
                offsetX = (screenW - mapW - Hud.Width) / 2;
            else if ((screenW - Hud.Width) / 2 > centerX)
                offsetX = Hud.Width;
            else if ((screenW  - Hud.Width) / 2> mapW - centerX)
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

            for (int i = (offsetX < 0 ? -offsetX : 0) / Size.MEDIUM; i < (offsetX < 0 ? -offsetX : 0) / Size.MEDIUM + screenW / Size.MEDIUM + 1; i++)
                for (int j = (offsetY < 0 ? -offsetY : 0) / Size.MEDIUM; j < (offsetY < 0 ? -offsetY : 0) / Size.MEDIUM + screenH / Size.MEDIUM + 1; j++)
                {
                    if (i >= width || j >= height)
                        break;
                    MapObject mo = terrain [i, j];
                    if (mo != null)
                    {
                        toDraw.Add(mo);
                    }
                }
            foreach (MapObject mo in objects)
            {
				if(isVisible(mo))
                	toDraw.Add(mo);
            }
            toDraw.Sort();
            foreach (MapObject mo in toDraw)
            {

                mo.draw(drawer, gameTime, offsetX, offsetY);
                //drawer.draw((int)mo.x+offsetX, (int)mo.y+offsetY, mo.getDrawInfo(), mo.rotation);
            }

            Fog.draw(screenW, screenH, centerX - Size.SMALL + offsetX, centerY - Size.SMALL + offsetY, 11.2f, drawer);       
		}

		private bool isVisible (MapObject mo)
		{
			double x = (focus.x - mo.x) / Size.MEDIUM;
			double y = (focus.y - mo.y) / Size.MEDIUM;
			return x * x + y * y < 11.2f * 11.2f;
		}
    }
}
