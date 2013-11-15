#include "TankStatbar.hpp"
#include "Exception.hpp"

TankStatbar::TankStatbar(Tank * tank, int width, int height)
{
  buffer = create_bitmap(width,height);
  if(!buffer)
    throw new Exception("Can not create TankStatbar bitmap");
  clear_to_color(buffer,makecol(25,25,25));

  this->tank = tank;
}
TankStatbar::~TankStatbar()
{
  // todo destroy bitmap
}

void TankStatbar::move()
{
  clear_to_color(buffer,makecol(25,25,25));

  int hi = 10;
  int lo = buffer->h - 10;

  int unitsPerBar = 3;
  int unitWidth = buffer->w / (4 * unitsPerBar + 5);

  int hpWidth = tank->getHp() * unitsPerBar * unitWidth / tank->getHpMax();
  rect(buffer,unitWidth,hi,unitWidth+unitWidth*unitsPerBar,lo,makecol(100,0,0));
  rectfill(buffer,unitWidth,hi,unitWidth+hpWidth,lo,makecol(100,0,0));

  int ammoWidth = tank->getAmmo() * unitsPerBar * unitWidth / tank->getAmmoMax();
  rect(buffer,unitWidth*2+unitsPerBar*unitWidth,hi,unitWidth*2+unitsPerBar*unitWidth+unitWidth*unitsPerBar,lo,makecol(0,100,0));
  rectfill(buffer,unitWidth*2+unitsPerBar*unitWidth,hi,unitWidth*2+unitsPerBar*unitWidth+ammoWidth,lo,makecol(0,100,0));

  int fuelWidth = tank->getFuel() * unitsPerBar * unitWidth / tank->getFuelMax();
  rect(buffer,unitWidth*3+unitsPerBar*unitWidth*2,hi,unitWidth*3+unitsPerBar*unitWidth*2+unitWidth*unitsPerBar,lo,makecol(96,51,17));
  rectfill(buffer,unitWidth*3+unitsPerBar*unitWidth*2,hi,unitWidth*3+unitsPerBar*unitWidth*2+fuelWidth,lo,makecol(96,51,17));

  int reloadWidth = tank->getReload() * unitsPerBar * unitWidth / tank->getReloadMax();
  rect(buffer,unitWidth*4+unitsPerBar*unitWidth*3,hi,unitWidth*4+unitsPerBar*unitWidth*3+unitWidth*unitsPerBar,lo,makecol(100,100,100));
  rectfill(buffer,unitWidth*4+unitsPerBar*unitWidth*3,hi,unitWidth*4+unitsPerBar*unitWidth*3+reloadWidth,lo,makecol(100,100,100));
}

BITMAP * TankStatbar::getBuffer()
{
  return buffer;
}
