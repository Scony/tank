#ifndef TANK_HPP
#define TANK_HPP

class Tank
{
public:
  Tank(int id, int x, int y, int rotation, int shoot, std::string nick, int r, int g, int b, int frags);
  int getId();
  std::string toString();

private:
  int id;
  int x;
  int y;
  int rotation;
  int shoot;
  std::string nick;
  int r;
  int g;
  int b;
  int frags;

};

#endif
