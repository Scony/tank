using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Tanks2014
{
    public class Spriter
    {
        private Texture2D sprite;
        private SpriteBatch spriteBatch;
		private Game host;

        public Spriter(Game host, SpriteBatch sb, Texture2D sprite)
        {
			this.host = host;
            spriteBatch = sb;
            this.sprite = sprite;
        }

        public void draw(int x, int y, DrawInfo d, Rotation rotation = Rotation.UP)
        {
            draw(x, y, d.size, d.spriteX, d.spriteY, (int)rotation);
        }

        public void draw(int x, int y, int size, int spriteX, int spriteY, int rotation)
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
            spriteBatch.Draw(sprite, new Rectangle(x + (int)size / 2, y + (int)size / 2, (int)size, (int)size), new Rectangle(spriteX, spriteY, (int)size, (int)size), Color.White, rotationAngle, new Vector2((int)size / 2, (int)size / 2), effect, 0);
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
