#ifndef _Player
#define _Player

#include <iostream>

#include "GameController.hpp"
#include "Group.hpp"
#include "Object.hpp"

class Group;

class Player : public IPlaceable {

  std::pair<int, int> _location;
  int _sunshine;
  // Unit: TILE/TICK
  int _speed;
  int _boost_timer;
  Object *_object = nullptr;
  Group *_group;
  /**
   * In our situation, every player should be created by
   * a group, so every time create a group, take the name
   * of group to the player.
   */

  friend class Group; // Player can only be created by Group.

public:
  Player(Group *g);
  ~Player();

  void setSunshine(int numOfSunshine);
  int getSunshine();
  void setObject(Object *objet);
  Object *getObject();
  void setSpeed(int speed);
  int getSpeed();
  void setBoostTimer(int boost_timer);
  int getBoostTimer();

  int getY() const {return _location.first;}
  int getX() const {return _location.second;}

  // void agir(); // il va agir,
  void seDeplacer();
  void useObject();
  int makeDecision();
  void setLocation(int, int);
  void setLocation(std::pair<int, int>);
  std::pair<int, int> getLocation() const;
  const Group *getGroup() const;
};

#endif
