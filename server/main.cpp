#include <iostream>

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"

#include "Tank.hpp"

#define LOBBY_PORT 1337
#define GAME_PORT 1338
#define GAME_SIZE 2
#define SERVER_LIMIT 128

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

  Tank tank(1,100,100,3,1);
  cout << tank.toString() << endl;

  while(true)
    {
      cout << "LOOP\n";
      // cpu save
      usleep(5000000);

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
	      // broadcast finish & close connections
	      // TODO: crate Game instance here and broadcast data
	      for(int i = 0; i < GAME_SIZE; i++)
		{
		  Poco::Net::SocketStream str(lss[i]);
		  str << "have game params, cya\n" << flush;
		  lss[i].close();
		}
	    }
      	}
      catch(Poco::IOException e)
	{
	  // broadcast actual state
	  for(int i = 0; i < lssi; i++)
	    {
	      Poco::Net::SocketStream str(lss[i]);
	      str << lssi << " " << GAME_SIZE << "\n" << flush;
	    }
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
		  // TODO: check if game exists
		  // if so, make update
		  // if not, return 0\n
		  cout << "GAME MESSAGE FROM #" << i << " TO GID #" << gid << endl;
		  if(gid == 1337)
		    str << "3 bla bla bla" << endl << flush;
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
