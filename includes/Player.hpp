#ifndef _Player
#define _Player

#include <iostream>

#include "GameController.hpp"
#include "Group.hpp"
#include "Object.hpp"

enum Direction { Up, Down, Left, Right };

class Group;

class Player : public IPlaceable {

  std::pair<int, int> _location;
  Direction _direction;
  int _sunshine;
  // Unit: TILE/TICK
  int _speed;
  int _boost_timer;
  Object *_object;
  Group *_group;
  /**
   * In our situation, every player should be created by
   * a group, so every time create a group, take the name
   * of group to the player.
   */

  friend class Group; // Player can only be created by Group.

public:
  Player(Group *g);

  void setSunshine(int numOfSunshine);
  int getSunshine();
  void setObject(Object *objet);
  Object *getObject();
  void setDirection(Direction direction);
  Direction getDirection();
  void setSpeed(int speed);
  int getSpeed();
  void setBoostTimer(int boost_timer);
  int getBoostTimer();

  void agir(); // il va agir,
  void seDeplacer();
  void useObject();
  int makeDecision();
  void setLocation(int, int);
  void setLocation(std::pair<int, int>);
  std::pair<int, int> getLocation() const;
  const Group *getGroup() const;
};

#endif
