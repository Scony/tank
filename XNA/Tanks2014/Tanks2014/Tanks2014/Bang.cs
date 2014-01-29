
using Microsoft.Xna.Framework;

namespace Tanks2014
{

	public class Bang : MapObject
		{
		private double time = 0.3;
		private int phase = 3;
		private int size;

		public Bang(int x, int y, int size){
			this.x = x;
			this.realX = x;
			this.y = y;
			this.realY = y;
			this.size = size;
		}

		private DrawInfo info = new DrawInfo(256, 64, 32);
			public override int getTypeId()
			{
				return 400;
			}

			public override DrawInfo getDrawInfo ()
			{
				return info;
			}

			public override void draw(Drawer drawer, Microsoft.Xna.Framework.GameTime gameTime, int offsetX, int offsetY)
			{
				drawer.draw((int)x + offsetX, (int)y+offsetY, size, info.size, info.spriteX, info.spriteY, (int)rotation, Color.White);
			}

			public override void update (Microsoft.Xna.Framework.GameTime gameTime, Map map)
			{
				time -= gameTime.ElapsedGameTime.TotalSeconds;
					if (phase == 3 && time < 0.2) {
						phase = 2;
						info.spriteX += 32;
					}
					if (phase == 2 && time < 0.1) {
						phase = 1;
						info.spriteX += 32;
					}
					if (phase == 1 && time < 0) {
						map.removeObject(this);
					}
				}
			}
}