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
        public Spriter(SpriteBatch sb, Texture2D sprite)
        {
            spriteBatch = sb;
            this.sprite = sprite;
        }

        public void draw(int x, int y, int width, int height, int spriteX, int spriteY, int rotation)
        {
            spriteBatch.Draw(sprite, new Rectangle(x, y, width, height), new Rectangle(spriteX, spriteY, width, height), Color.White, rotation * (float)Math.PI / 180, new Vector2(width / 2, height / 2), SpriteEffects.None, 0);
        }
    }
}
