using System;

namespace Tanks2014
{
//    class Grenade : Weapon
//    {
//		new class Projectible : Weapon.Projectible
//		{
//			int phase = 0;
//			DrawInfo info = fly;
//			static DrawInfo fly = new DrawInfo(16,16,Size.SMALL);
//			static DrawInfo explosion = new DrawInfo(7*64,128,Size.LARGE);
//
//			public Projectible(double x, double y, Rotation rot) : base(x,y,rot, 1000, Size.LARGE * 2)
//			{
//			}
//			public override int getTypeId ()
//			{
//				return 202;
//			}
//			public override DrawInfo getDrawInfo ()
//			{
//				return info;
//			}
//			public override void update (Microsoft.Xna.Framework.GameTime gameTime, Map map)
//			{
//				if (phase == 0) {
//					if (traveled > range) {
//						phase = 1;
//						info = explosion;
//					} else if (rotation == Rotation.LEFT) {
//						x -= speed * gameTime.ElapsedGameTime.TotalSeconds;
//					} else if (rotation == Rotation.RIGHT) {
//						x += speed * gameTime.ElapsedGameTime.TotalSeconds;
//					} else if (rotation == Rotation.UP) {
//						y -= speed * gameTime.ElapsedGameTime.TotalSeconds;
//					} else if (rotation == Rotation.DOWN) {
//						y += speed * gameTime.ElapsedGameTime.TotalSeconds;
//					}
//					traveled += speed * gameTime.ElapsedGameTime.TotalSeconds;
//				}
//				if (phase > 0) {
//					info.spriteX += Size.LARGE;
//					phase++;
//				}
//				if (phase == 4) {
//					map.removeObject(this);
//				}
//			}
//		}
//		public override bool shoot(double x, double y, Rotation rot, Map map)
//		{
//			if (reload <= 0) {
//				map.addObject(new Projectible(x,y,rot));
//				reload = 5;
//                return true;
//			}
//            return false;
//		}
//    }
}

