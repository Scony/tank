#include <iostream>

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"

#define LOBBY_PORT 1337
#define GAME_PORT 1338
#define GAME_SIZE 2

int main(int argc, char** argv)
{
  Poco::Net::ServerSocket lobby(LOBBY_PORT);
  Poco::Net::ServerSocket game(GAME_PORT);

  Poco::Net::StreamSocket lss[GAME_SIZE];
  int lssi = 0;

  lobby.setBlocking(false);
  game.setBlocking(false);

  while(true)
    {
      // cpu save
      usleep(5000000);

      // lobby accepts + grouping
      try
      	{
	  lss[lssi] = lobby.acceptConnection();
	  std::cout << lssi++ << std::endl;

	  // broadcast actual state
	  for(int i = 0; i < lssi; i++)
	    {
	      Poco::Net::SocketStream str(lss[i]);
	      str << lssi << " " << GAME_SIZE << "\n" << std::flush;
	    }

	  // grouping finished
	  if(lssi == GAME_SIZE)
	    {
	      lssi = 0;
	      // broadcast finish & close connections
	      for(int i = 0; i < GAME_SIZE; i++)
		{
		  Poco::Net::SocketStream str(lss[i]);
		  str << "have game params, cya\n" << std::flush;
		  lss[i].close();
		}
	    }
	  // ss.setReceiveTimeout(Poco::Timespan(5,0));
	  // Poco::Net::SocketStream str(ss);
	  // std::string msg;
	  // str >> msg;
	  // std::cout << msg << std::endl;
      	}
      catch(Poco::IOException e)
	{
	  // broadcast actual state
	  for(int i = 0; i < lssi; i++)
	    {
	      Poco::Net::SocketStream str(lss[i]);
	      str << lssi << " " << GAME_SIZE << "\n" << std::flush;
	    }
	}

      // game accepts + handler
      // here
    }

  return 0;
}
