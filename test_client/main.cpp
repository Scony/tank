#include <allegro.h>

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"

#include <iostream>
#include <sstream>
#include <string>

#define LOBBY_PORT 1337
#define GAME_PORT 1338

using namespace Poco::Net;
// using namespace Poco;
using namespace std;

string int2str(int x)
{
  stringstream ss;
  ss << x;

  return ss.str();
}

volatile long speed = 0;
volatile int close_button = 0;

void close_button_handler()
{
  close_button = 1;
}
END_OF_FUNCTION(close_button_handler);

void increment_speed()
{
  speed++;
}
END_OF_FUNCTION(increment_speed);

LOCK_VARIABLE(speed);
LOCK_FUNCTION(increment_speed);
LOCK_FUNCTION(close_button_handler);

int main(int argc, char ** argv)
{
  allegro_init();
  install_keyboard();
  install_timer();
  install_int_ex(increment_speed,BPS_TO_TIMER(100));
  set_close_button_callback(close_button_handler);
  set_color_depth(desktop_color_depth());
  set_gfx_mode(GFX_AUTODETECT_WINDOWED,500,500,0,0);

  clear_to_color(screen,makecol(255,255,255));

  int x;
  int y;
  int gid;
  int tid;

  string ip;
  cin >> ip;

  // handshake start
  Poco::Net::SocketAddress hsa(ip,1337);
  Poco::Net::StreamSocket hsocket(hsa);
  Poco::Net::SocketStream hstr(hsocket);

  while(true)
    {
      int connections;
      int totalConnections;
      hstr >> connections >> totalConnections;
      // cout << connections << " " << totalConnections << endl;
      if(connections == totalConnections)
	{
	  string stmp;
	  int itmp;
	  hstr >> stmp >> stmp;
	  hstr >> gid >> tid >> x >> y >> itmp >> itmp;
	  break;
	}
    }
  // handshake end

  BITMAP * buffer = create_bitmap(500,500);
  clear_to_color(buffer,makecol(255,255,255));
  BITMAP * obj = create_bitmap(8,8);
  clear_to_color(obj,makecol(0,0,0));

  // network transfer init start
  Poco::Net::SocketAddress tsa(ip,1338);
  Poco::Net::StreamSocket tsocket(tsa);
  Poco::Net::SocketStream tstr(tsocket);
  // network transfer init end

  while(!close_button)
    {
      for(; speed > 0 && !close_button; speed--)
	{
	  clear_to_color(buffer,makecol(255,255,255));

	  if(key[KEY_UP])
	    y -= 10;
	  if(key[KEY_DOWN])
	    y += 10;
	  if(key[KEY_LEFT])
	    x -= 10;
	  if(key[KEY_RIGHT])
	    x += 10;

	  // network transfer start
	  tstr << gid << " " << tid << " " << x << " " << y << " " << 0 << " " << 0 << " " << 0 << endl << flush;

	  int state;
	  tstr >> state;
	  if(!state)
	    return 0;

	  int count;
	  tstr >> count;
	  // cout << state << " " << count << endl;
	  for(int i = 0; i < count; i++)
	    {
	      int rid;
	      int rx;
	      int ry;
	      int rtmp;

	      tstr >> rid >> rx >> ry >> rtmp >> rtmp;
	      // cout << rid << " " << rx << " " << ry << " " << rtmp << endl;
	      if(rid == tid)
		{
		  x = rx;
		  y = ry;
		}
	      blit(obj,buffer,0,0,rx,ry,8,8);
	    }
	  // network transfer end

	  blit(buffer,screen,0,0,0,0,500,500);
	}
    }

  destroy_bitmap(obj);
  destroy_bitmap(buffer);

  remove_int(increment_speed);
  allegro_exit();

  return 0;
}

END_OF_MAIN();
