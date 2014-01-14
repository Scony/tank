using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tanks2014
{
    public abstract class Tank : MapObject
    {
        protected int hp;
        protected int maxHp;
        protected int fuel;
        protected int maxFuel;
        protected Weapon[] weapons = new Weapon[10];
		protected int activeWeapon = 0;

        public Tank()
        {
            weapons[0] = new Cannon();
        }
        
        public override int getTypeId()
        {
            return 100;
        }
    }
}
