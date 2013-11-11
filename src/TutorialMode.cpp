#include "TutorialMode.hpp"
#include "TutorialMap.hpp"
#include "PlayerTank.hpp"
#include "Player2Tank.hpp"
#include "AITank.hpp"

TutorialMode::TutorialMode(BITMAP * screen) : Mode(screen)
{
  spriter = new Spriter("/home/scony/Allegro/tank/src/sprite.bmp");
  policy = new PolicyManager("/home/scony/Allegro/tank/src/policy.dat");
  TutorialMap * tmap = new TutorialMap(spriter,policy,"/home/scony/Allegro/tank/src/medium.map");

  player1 = new PlayerTank(spriter,1,1,1,100,100,1000,1000,0,10);
  tmap->addTank(player1);
  tmap->addTank(new Player2Tank(spriter,1,1,1,100,100,1000,1000,0,10));
  for(int i = 0; i < 2; i++)
    tmap->addTank(new AITank(spriter,1,1,1,100,100,1000,1000,0,10));

  map = tmap;
}

TutorialMode::~TutorialMode()
{
  delete map;
  delete policy;
  delete spriter;
}

void TutorialMode::move()
{
  map->move();
}

void TutorialMode::draw()
{
  // debug todo
  if(player1 && player1->isDeath())
    player1 = NULL;
  if(player1 && rand() % 10 > 8)
    set_window_title(player1->toString().c_str());

  BITMAP * buff = map->getBuffer();
  Point focus = map->getFocus();

  int buffX;
  int buffY;
  int screenX;
  int screenY;
  int wtc;
  int htc;

  // X axis calculations
  if(buff->w <= screen->w)
    {
      buffX = 0;
      screenX = (screen->w - buff->w) / 2;
      wtc = buff->w;
    }
  else
    {
      buffX = focus.getX() - (screen->w / 2);
      buffX = buffX < 0 ? 0 : buffX;
      buffX = buffX > buff->w - screen->w ? buff->w - screen->w : buffX;
      screenX = 0;
      wtc = screen->w;
    }

  // Y axis calculations
  if(buff->h <= screen->h)
    {
      buffY = 0;
      screenY = (screen->h - buff->h) / 2;
      htc = buff->h;
    }
  else
    {
      buffY = focus.getY() - (screen->h / 2);
      buffY = buffY < 0 ? 0 : buffY;
      buffY = buffY > buff->h - screen->h ? buff->h - screen->h : buffY;
      screenY = 0;
      htc = screen->h;
    }

  blit(buff,			// from
       screen,			// to
       buffX,			// start-point-x in buffer
       buffY,			// start-point-y in buffer
       screenX,			// start-point-x in screen
       screenY,			// start-point-y in screen
       wtc,			// width to copy from buffer
       htc);			// height to copy from buffer
}