/**
 *
 * \file GameController.hpp
 * \brief Header for our Singleton GameController class
 * \author Cliquot Théo, Benquet Matthias
 * \date 12/02/2023
 *
 **/

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/

#include "Map.hpp"
#include "Player.hpp"
#include "Sun.hpp"
#include "f_stack.hpp"
#include "p_queue.hpp"
#include <list>

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/

class Map;
class Player;
class Group;

/**
 *
 * \class GameController
 * \brief The controller to manage a game
 *
 * Follow the singleton pattern
 *
 **/

class GameController {
  friend Map; // friend to simplify our code

  /******************************* Attribute *********************************/

private:
  static GameController *game; // The only GameController instantiate
  static Map *map;             // The map this gameController manage
  int nbrPlayer = 8;
  int nbrSun = 5;
  Player **players;
  Sun **suns;
  IPlaceable **objects;

  Group *g1;
  Group *g2;

  /********************************* Method ***********************************/

  /***************************** Private Method ******************************/
  /****************************** Constructor ********************************/

  GameController(); // Must be private for a singleton pattern
  GameController(int nbrPlayer, int height, int width); // Same

public:
  /****************************** Public Method ******************************/

  GameController(const GameController &) = delete; // Remove default
  void operator=(const GameController &) = delete; // Same

  /**
   *
   * \fn  void CreateGame();
   * \brief Create a Game
   * \param None
   * \return Null
   *
   **/

  void CreateGame();

  /**
   *
   * \fn  void InitGame();
   * \brief Init a Game
   * \param None
   * \return Null
   *
   **/

  void InitGame();

  /**
   *
   * \fn  void NewRound();
   * \brief Play a round in the present game
   * \param None
   * \return Null
   *
   **/

  void NewRound();

  /**
   *
   * \fn  void ManagePlayers();
   * \brief Manage the player in the game
   * \param None
   * \return Null
   *
   **/

  void ManagePlayers();

  /**
   *
   * \fn  void ManageBoxes();
   * \brief Manage the boxes in the game
   * \param None
   * \return Null
   *
   **/

  void ManageBoxes();

  /**
   *
   * \fn  void ManageObjects();
   * \brief Manage the objects in the game
   * \param None
   * \return Null
   *
   **/

  void ManageObjects();

  /**
   *
   * \fn  int EvaluateTile();
   * \brief return a "score" for a certain tile
   * \param int: the y axis of the tile to analyse
   * \param int: the x axis of the tile to analyse
   * \return the score of this tile
   *
   **/

  int EvaluateTile(int, int);

  /**
   *
   * \fn std::pair<int, int> A(std::pair<int, int> start, std::pair<int, int>
   *end); \brief Apply the A pathfinding algorithm to the actual game. \param
   *std::pair<int, int> start : the tile where to start \param std::pair<int,
   *int> end: the objectif to approach \return the next tiles to approach the
   *end.
   *
   **/

  std::pair<int, int> A(std::pair<int, int> start, std::pair<int, int> end);

  /**
   *
   * \fn  void loseSun(Player *);
   * \brief Function to call when a player lose a sun
   * \param Player * : Which player must lose the sun
   * \return Null
   *
   **/

  void loseSun(Player *);

  /**
   *
   * \fn  std::pair<int, int> findFreeTile(Player *);
   * \brief Find a free Tile close to a Player
   * \param Player * : The player of reference
   * \return std::pair<int,int>: the position of the free tile
   *
   **/

  std::pair<int, int> findFreeTile(Player *);

  /**
   *
   * \fn  PlayerHere(std::pair<int, int>);
   * \brief Return if a player is on this position
   * \param std::pair<int,int>: the position to test
   * \return bool: if a player is here or not
   *
   **/

  bool PlayerHere(std::pair<int, int>);

  /**
   *
   * \fn PLaceNewObject(Iplaceable *);
   * \brief Place a new object on the map
   * \param IPlaceable *: The object to place
   * \return Null
   *
   **/

  void PlaceNewObject(IPlaceable *);

  /**
   *
   * \fn static GameController *Get(int = 8);
   * \brief get the unique gameController or create one
   * \param int: the number of player
   * \return the unique GameController
   *
   **/

  static GameController *Get(int = 8);

  /**
   *
   * \fn void Destroy();
   * \brief Replace the destructor
   * \param None
   * \return Null
   *
   **/

  void Destroy();

  // Never use it, infinit loop !!!
  //~GameController();
};

#endif /* GAMECONTROLLER_H */
