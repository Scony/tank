﻿using System;
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
                    case 1:
                        Ammo ammo = new Ammo(amount);
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

        public void addObject(MapObject obj)
        {
            objects.Add(obj);
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
                    if(obj.getTypeId() == 100 && terrain[i,j] != null && (terrain[i,j].getTypeId() == 1 || terrain[i,j].getTypeId() == 2 || terrain[i,j].getTypeId() == 5))
                    {
                        obj.revert();
                        return;
                    }
                    if((obj.getTypeId() == 200 || obj.getTypeId() == 201) && terrain[i,j] != null && terrain[i,j].getTypeId() == 1)
                    {
                        obj.deleted = true;
                        toRemove.Add(obj);
                        terrain[i,j] = null;
                    }
                    if((obj.getTypeId() == 200 || obj.getTypeId() == 201) && terrain[i,j] != null && terrain[i,j].getTypeId() == 2)
                    {
                        obj.deleted = true;
                        toRemove.Add(obj);
                        return;
                    }
                }
            }

        }

        protected void checkObjectsCollision(MapObject obj, int idx)
        {
            for (int i = idx+1; i<objects.Count; i++)
            {
                if (collides(obj, objects [i]))
                {
                    if (obj.collisionId > objects [i].collisionId)
                    {
                        obj.handleCollision(objects [i]);
                    } else
                    {
                        objects [i].handleCollision(obj);
                    }
                }
            }
        }

        public bool collides(MapObject o1, MapObject o2)
        {
            int x11 = (int)o1.realX;
            int y11 = (int)o1.realY;
            int x12 = (int)o1.realX + (int)o1.getDrawInfo().size - 1;
            int y12 = (int)o1.realY + (int)o1.getDrawInfo().size - 1;

            int x21 = (int)o2.realX;
            int y21 = (int)o2.realY;
            int x22 = (int)o2.realX + (int)o2.getDrawInfo().size - 1;
            int y22 = (int)o2.realY + (int)o2.getDrawInfo().size - 1;


            if ((x11 <= x21 && x21 <= x12 && y11 <= y21 && y21 <= y12) ||
                (x11 <= x21 && x21 <= x12 && y11 <= y22 && y22 <= y12) ||
                (x11 <= x22 && x22 <= x12 && y11 <= y22 && y22 <= y12) ||
                (x11 <= x22 && x22 <= x12 && y11 <= y21 && y21 <= y12))
                return true;

            return false;
        }

        public void draw(GameTime gameTime, Spriter drawer)
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
