using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tanks2014
{
    public abstract class Tank : MapObject
    {
        int hp;
        int maxHp;
        int fuel;
        int maxFuel;
        Weapon[] weapons = new Weapon[10];

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
