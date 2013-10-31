#include "TutorialGame.hpp"
#include "TutorialMap.hpp"

TutorialGame::TutorialGame(BITMAP * screen) : Game(screen)
{
  spriter = new Spriter("/home/scony/Allegro/tank/src/sprite.bmp");
  map = new TutorialMap(spriter,100,100);
}

TutorialGame::~TutorialGame()
{
  delete map;
  delete spriter;
}

void TutorialGame::move()
{
  map->move();
}

void TutorialGame::draw()
{
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
