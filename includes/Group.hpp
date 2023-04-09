/**
 *
 * \file Group.hpp
 * \brief Header for our Group class
 * \author XIE Ao
 * \date 01/02/2023
 *
 **/

#ifndef _Group
#define _Group

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/

#include "Player.hpp"
#include <iostream>
#include <string>

/*****************************************************************************/
/*                                                                           */
/*                                 Constant                                  */
/*                                                                           */
/*****************************************************************************/

const int NUM_PLAYER = 4;

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/

class Player;

/**
 *
 * \class Group
 * \brief Represent a group of player
 *
 **/

class Group {

private:
  /******************************* Attribute *********************************/

  int _id;
  std::string _name;
  int _num_player;
  Player *players[NUM_PLAYER];

public:
  /****************************** Public Method ******************************/
  /****************************** Constructor ********************************/

  /**
   *
   * \fn Group()
   *  \brief Constructor for GameController
   * \return An new object GameController
   *
   **/

  Group();

  /**
   *
   * \fn Group(int id)
   *  \brief Constructor for GameController with id
   * \return An new object GameController
   *
   **/

  Group(int id);

  /**
   *
   * \fn Group(int id, std::string name)
   *  \brief Constructor for GameController with id and name
   * \return An new object GameController
   *
   **/

  Group(int id, std::string name);

  /******************************* Destructor ********************************/

  /**
   *
   * \brief Destructor for Group
   *
   **/

  ~Group();

  /********************************** Other **********************************/

  /**
   *
   * \fn void AddPlayer(Player *p)
   * \brief Add a player tp this group
   * \param Player *p: the player to add
   * \return Null
   *
   **/

  void AddPlayer(Player *p);

  /**
   *
   * \fn  bool SameGroup(const Group *g) const;
   * \brief Compare if the group give is this group
   * \param Group *g: Group to test
   * \return bool if it's the case, false else
   *
   * COULD BE REMPLACE WITH THE OPERATOR==
   *
   **/

  bool SameGroup(const Group *g) const;

  /**
   *
   * \fn bool OnMyGroup(const Player *p) const;
   * \brief Test if a player is a member of this group
   * \param Player *p: the player to test
   * \return True if it's the case, false else
   *
   **/

  bool OnMyGroup(const Player *p) const;

  /**
   * 
   * \fn int getScore() const;
   * \brief Get the score of the group
   * \return int the score
  */
  int getScore() const;
};

#endif
