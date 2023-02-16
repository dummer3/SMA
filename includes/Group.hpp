#ifndef _Group
#define _Group

const int NUM_PLAYER = 4;

#include "Player.hpp"
#include <iostream>
#include <string>

class Player;

class Group {
private:
  int _id;
  std::string _name;
  int _num_player;
  Player *players[NUM_PLAYER];

public:
  Group();
  Group(int id);
  Group(int id, std::string name);
  void AddPlayer(Player *p);
  bool SameGroup(const Group *g) const;
  bool OnMyGroup(const Player *p) const;
};

#endif
