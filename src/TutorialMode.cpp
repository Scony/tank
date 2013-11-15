#include "TutorialMode.hpp"
#include "TutorialMap.hpp"
#include "Configuration.hpp"
#include "PlayerTank.hpp"
#include "Player2Tank.hpp"
#include "AITank.hpp"

TutorialMode::TutorialMode(BITMAP * screen) : Mode(screen)
{
  spriter = new Spriter(Configuration::getInstance()->getPath() + "sprite.bmp");
  policy = new PolicyManager(Configuration::getInstance()->getPath() + "policy.dat");
  TutorialMap * tmap = new TutorialMap(spriter,policy,Configuration::getInstance()->getPath() + "medium.map");
  player1 = new PlayerTank(spriter,1,1,1,100,100,5000,5000,0,70);
  tsb = new TankStatbar(player1,screen->w,30);

  tmap->addTankS(player1);
  tmap->addTankS(new Player2Tank(spriter,1,1,1,100,100,5000,5000,0,70));
  for(int i = 0; i < 2; i++)
    tmap->addTankS(new AITank(spriter,1,1,1,100,100,10000,10000,0,70));

  map = tmap;
}

TutorialMode::~TutorialMode()
{
  delete tsb;
  delete map;
  delete policy;
  delete spriter;
}

void TutorialMode::move()
{
  map->move();

  if(player1 && player1->isDeath())
    player1 = NULL;

  if(player1)
    tsb->move();
}

void TutorialMode::draw()
{
  BITMAP * tsbBuff = tsb->getBuffer();
  BITMAP * mBuff = map->getBuffer();
  Point focus = map->getFocus();

  int mBuffX;
  int mBuffY;
  int screenX;
  int screenY;
  int wtc;
  int htc;

  // X axis calculations
  if(mBuff->w <= screen->w)
    {
      mBuffX = 0;
      screenX = (screen->w - mBuff->w) / 2;
      wtc = mBuff->w;
    }
  else
    {
      mBuffX = focus.getX() - (screen->w / 2);
      mBuffX = mBuffX < 0 ? 0 : mBuffX;
      mBuffX = mBuffX > mBuff->w - screen->w ? mBuff->w - screen->w : mBuffX;
      screenX = 0;
      wtc = screen->w;
    }

  // Y axis calculations
  if(mBuff->h <= screen->h - tsbBuff->h)
    {
      mBuffY = 0;
      screenY = (screen->h - tsbBuff->h - mBuff->h) / 2;
      htc = mBuff->h;
    }
  else
    {
      mBuffY = focus.getY() - ((screen->h - tsbBuff->h) / 2);
      mBuffY = mBuffY < 0 ? 0 : mBuffY;
      mBuffY = mBuffY > mBuff->h - (screen->h - tsbBuff->h) ? mBuff->h - (screen->h - tsbBuff->h) : mBuffY;
      screenY = 0;
      htc = screen->h - tsbBuff->h;
    }

  blit(tsbBuff,			// from
       screen,			// to
       0,			// start-point-x in buffer
       0,			// start-point-y in buffer
       0,			// start-point-x in screen
       0,			// start-point-y in screen
       tsbBuff->w,		// width to copy from buffer
       tsbBuff->h);		// height to copy from buffer

  blit(mBuff,			// from
       screen,			// to
       mBuffX,			// start-point-x in buffer
       mBuffY,			// start-point-y in buffer
       screenX,			// start-point-x in screen
       screenY + tsbBuff->h,	// start-point-y in screen
       wtc,			// width to copy from buffer
       htc);			// height to copy from buffer
}
