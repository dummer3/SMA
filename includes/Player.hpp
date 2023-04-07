/**
 *
 * \file Player.hpp
 * \brief Header for our Player class
 * \author XIE Ao
 * \date 01/02/2023
 *
 **/

#ifndef _Player
#define _Player

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/

#include <iostream>

#include "GameController.hpp"
#include "Group.hpp"
#include "Object.hpp"

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/

class Group;

/**
 *
 * \class Player
 * \brief Represent a player in our game
 *
 * Implement IPlaceable interface
 *
 **/

class Player : public IPlaceable {

  /******************************* Attribute *********************************/
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
  /****************************** Public Method ******************************/
  /****************************** Constructor ********************************/

  /**
   *
   * \fn Player(Group* g)
   * \brief Constructor for Player with a initial Group
   * \return An new object Player
   *
   **/

  Player(Group *g);

  /******************************* Destructor ********************************/

  /**
   *
   * \brief Destructor for Player
   *
   **/
  ~Player();

  /********************************** Other **********************************/

  void setSunshine(int numOfSunshine);
  int getSunshine();
  void setObject(Object *objet);
  Object *getObject();
  void setSpeed(int speed);
  int getSpeed();
  void setBoostTimer(int boost_timer);
  int getBoostTimer();

  int getY() const { return _location.first; }
  int getX() const { return _location.second; }
  void setLocation(int, int);
  void setLocation(std::pair<int, int>);
  std::pair<int, int> getLocation() const;
  const Group *getGroup() const;

  /**
   *
   * \fn void seDeplacer();
   * \brief The player choose where he want to move, and set is location
   * \param None
   * \return Null
   *
   **/
  void seDeplacer();

  /**
   *
   * \fn void useObject();
   * \brief The player use his object, consume it
   * \param None
   * \return Null
   *
   **/
  void useObject();

  /**
   *
   * \fn int makeDecision()
   * \brief action a player make during a round
   * \param None
   * \return int, 1 if he uses a object, 2 if he moves
   *
   **/

  int makeDecision();
};

#endif
