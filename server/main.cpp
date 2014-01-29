#include <iostream>
#include <list>

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"

#include "Game.hpp"

#define LOBBY_PORT 1337
#define GAME_PORT 1338
#define SERVER_LIMIT 128
#define CPU_SAVE_US 1

using namespace std;

int main(int argc, char** argv)
{
  Poco::Net::ServerSocket lobby(LOBBY_PORT);
  Poco::Net::ServerSocket game(GAME_PORT);

  Poco::Net::StreamSocket lss[GAME_SIZE];
  Poco::Net::StreamSocket gss[SERVER_LIMIT];
  int lssi = 0;
  int gssc = 0;

  lobby.setBlocking(false);
  game.setBlocking(false);

  list<Game> games;

  while(true)
    {
      // cpu save
      usleep(CPU_SAVE_US);

      // lobby accepts + grouping
      try
      	{
	  lss[lssi] = lobby.acceptConnection();
	  cout << "LOBBY ACCEPT " << ++lssi << "/" << GAME_SIZE << endl;

	  // broadcast actual state
	  for(int i = 0; i < lssi; i++)
	    {
	      Poco::Net::SocketStream str(lss[i]);
	      str << lssi << " " << GAME_SIZE << "\n" << flush;
	    }

	  // grouping finished
	  if(lssi == GAME_SIZE)
	    {
	      lssi = 0;
	      // create Game & broadcast its data & close connections
	      Game game;
	      games.push_back(game);
	      for(int i = 0; i < GAME_SIZE; i++)
		{
		  Poco::Net::SocketStream str(lss[i]);
		  str << game.getInitData(i) << endl << flush;
		  lss[i].close();
		}
	    }
      	}
      catch(Poco::IOException e)
	{
	}

      // game accepts
      try
      	{
	  gss[gssc] = game.acceptConnection();
	  gss[gssc].setReceiveTimeout(Poco::Timespan(0,1));
	  cout << "GAME ACCEPT #" << gssc++ << endl;
      	}
      catch(Poco::IOException e)
      	{
      	}

      // game handler
      for(int i = 0; i < gssc; i++)
	{
	  try
	    {
	      Poco::Net::SocketStream str(gss[i]);
	      int gid;
	      if(str.peek() != -1) // message is valid
		{
		  str >> gid;

		  // ended games cleanout
		  list<Game>::iterator it = games.begin();
		  for(; it != games.end(); it++)
		    if(it->getId() == gid)
		      {
			if(!it->isOver())
			  break;
			else
			  it = games.erase(it);
		      }

		  // target game exists
		  if(it != games.end())
		    {
		      cout << "GAME MESSAGE FROM #" << i << " TO GID #" << gid << endl;

		      int id;
		      int x;
		      int y;
		      int rotation;
		      int shoot;
		      string nick;
		      int r;
		      int g;
		      int b;
		      int frags;

		      str >> id >> x >> y >> rotation >> shoot >> nick >> r >> g >> b >> frags;
		      it->updateTank(id,x,y,rotation,shoot,nick,r,g,b,frags);

		      int nDeaths;

		      str >> nDeaths;
		      for(int j = 0; j < nDeaths; j++)
			{
			  str >> id;
			  it->deleteTank(id);
			}

		      str << it->getData() << endl << flush;
		    }
		  else
		    str << "0" << endl << flush;
		}
	    }
	  catch(Poco::TimeoutException e)
	    {
	    }
	}
    }

  return 0;
}
