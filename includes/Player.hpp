#ifndef _Player
#define _Player

#include <iostream>

#include "Object.hpp"
#include "Group.hpp"

enum Direction {
  Up,
  Down,
  Left,
  Right
};

class Player {

  std::pair<int, int> _location;
  Direction _direction;
  int _sunshine;
  // Unit: TILE/TICK
  int _speed;
  Object * _object;
  Group _group;
  /**
   * In our situation, every player should be created by
   * a group, so every time create a group, take the name
   * of group to the player.
   */

  friend class Group; // Player can only be created by Group.

public:
  Player(Group g);

  void setSunshine(int numOfSunshine);
  int getSunshine();
  void setObject(Object * objet);
  Object * getObject();
  void setDirection(Direction direction);
  Direction getDirection();

  void agir(); // il va agir,
  void seDeplacer();
  void useObject();
  void makeDecision();
  void makeDecision();
  void seDeplacer();
};

#endif
