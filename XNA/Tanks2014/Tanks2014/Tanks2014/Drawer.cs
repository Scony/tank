using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public class Drawer
    {
        private Texture2D sprite;
        private SpriteBatch spriteBatch;
		private Game host;

        public Drawer(Game host, SpriteBatch sb, Texture2D sprite)
        {
			this.host = host;
            spriteBatch = sb;
            this.sprite = sprite;
        }
		public void drawText (int x, int y, String text)
		{
			drawText(x,y,text,Color.White);
		}
		public void drawText (int x, int y, String text, Color color)
		{
			for (int i=0; i<text.Length; i++) {
				int spriteX=0, spriteY=976;
				if(text[i] >= 'a' && text[i] <= 'z'){
					spriteY = 1024 - Size.LARGE;
					spriteX = Size.MEDIUM * (text[i] - 'a');
				}
				if(text[i] >= 'A' && text[i] <= 'Z'){
					spriteY = 1024 - Size.LARGE;
					spriteX = Size.MEDIUM * (text[i] - 'A');
				}
				if(text[i] >= '0' && text[i] <= '9'){
					spriteY = 1024 - Size.MEDIUM;
					spriteX = Size.MEDIUM * (text[i] - '0');
				}
				if(text[i] == '-'){
					spriteY = 1024 - Size.MEDIUM;
					spriteX = Size.MEDIUM * 16;
				}
				spriteBatch.Draw(sprite,
					new Rectangle(x + i*Size.MEDIUM + Size.SMALL, y + Size.SMALL, Size.MEDIUM, Size.MEDIUM),
				    new Rectangle(spriteX, spriteY, Size.MEDIUM, Size.MEDIUM),
				    color);
			}
		}

        public void draw(int x, int y, DrawInfo d, Rotation rotation = Rotation.UP)
        {
            draw(x, y, d.size, d.spriteX, d.spriteY, (int)rotation);
        }

		public void draw(int x, int y, DrawInfo d, Rotation rotation, Color color)
        {
			draw(x, y, d.size, d.spriteX, d.spriteY, (int)rotation, color);
        }

		public void draw (int x, int y, int size, int spriteX, int spriteY, int rotation)
		{
			draw(x,  y,  size, spriteX,  spriteY,  rotation, Color.White);
		}
		public void draw (int x, int y, int size, int spriteX, int spriteY, int rotation, Color color)
		{
			draw (x, y, size, size, spriteX, spriteY, rotation, color);
		}
        public void draw(int x, int y, int size, int spriteSize, int spriteX, int spriteY, int rotation, Color color)
        {
            SpriteEffects effect = SpriteEffects.None;
            float rotationAngle = 0;
            if (rotation == 1)
            {
                rotationAngle = (float)Math.PI / 2;
            }
            if (rotation == 2)
            {
                effect = SpriteEffects.FlipVertically;
            }
            if (rotation == 3)
            {
                rotationAngle = (float)Math.PI / 2;
                effect = SpriteEffects.FlipVertically;
            }
            if (rotation == 4)
            {
                rotationAngle = (float)Math.PI;
            }
            spriteBatch.Draw(sprite, new Rectangle(x + (int)size / 2, y + (int)size / 2, (int)size, (int)size), new Rectangle(spriteX, spriteY, (int)spriteSize, (int)spriteSize), color, rotationAngle, new Vector2((int)size / 2, (int)size / 2), effect, 0);
        }

		public void drawRect(int x, int y, int sizeX, int sizeY, Color color)
		{
			spriteBatch.Draw(sprite, 
				new Rectangle(x, y, sizeX, sizeY),
			    new Rectangle(8, 16, 2, 2),
			    color);
		}

		public int getScreenWidth()
		{
			return host.GraphicsDevice.Viewport.Width;
		}

		public int getScreenHeight()
		{
			return host.GraphicsDevice.Viewport.Height;
		}
    }
}
