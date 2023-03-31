/**
 *
 * \file Map.hpp
 * \brief Header for our Map class
 * \author Cliquot Théo
 * \date 21/01/2023
 *
 **/

#ifndef __MAP_HPP__
#define __MAP_HPP__

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/

#include "Box.hpp"
#include "GameController.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>

/*****************************************************************************/
/*                                                                           */
/*                                 Constant                                  */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*                             Color Constant                                */
/*****************************************************************************/

const std::string COLOR_BACK_DEF = "\x1b[m";
const std::string COLOR_BACK_BLACK = "\x1b[40m";
const std::string COLOR_BACK_RED = "\x1b[41m";
const std::string COLOR_BACK_GREEN = "\x1b[42m";
const std::string COLOR_BACK_YELLOW = "\x1b[43m";
const std::string COLOR_BACK_BLUE = "\x1b[44m";
const std::string COLOR_BACK_MAGENTA = "\x1b[45m";
const std::string COLOR_BACK_CYAN = "\x1b[46m";
const std::string COLOR_BACK_WHITE = "\x1b[47m";

const std::string COLOR_DEF = "\x1b[m";
const std::string COLOR_BLACK = "\x1b[30m";
const std::string COLOR_RED = "\x1b[31m";
const std::string COLOR_GREEN = "\x1b[32m";
const std::string COLOR_YELLOW = "\x1b[33m";
const std::string COLOR_BLUE = "\x1b[34m";
const std::string COLOR_MAGENTA = "\x1b[35m";
const std::string COLOR_CYAN = "\x1b[36m";
const std::string COLOR_WHITE = "\x1b[37m";

/*****************************************************************************/
/*                            Length Constant                                */
/*****************************************************************************/

const int MAX_WIDTH = 100;
const int MAX_HEIGHT = 100;

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/
class GameController;
class Group;

class Map {

  friend GameController;
  /******************************* Attribute *********************************/

private:
  int height;
  int width;
  int nbrBox = 4;

  /* Tiles meaning:
   * -1 : Obstacle
   * 0 : Empty tiles
   * 1xx : Box (with index xx in the boxs table)
   * 10xx: Sun (with index xx in the suns table)
   */

  int tiles[MAX_HEIGHT][MAX_WIDTH];
  Box **boxs;

  /********************************* Method ***********************************/

  /***************************** Private Method ******************************/
private:
  /**
   *
   * \brief Initialize every Sun and Box
   * \return Null
   *
   **/
  void InitBS();

  /**
   *
   * \brief Clean every Sun and Box
   * \return Null
   *
   **/
  void DeleteBS();

  /**
   *
   * \brief Add the element on coordinate [x,y] inside the suns array
   * \param int y: coordinate on the y-axis
   * \param int x: coordinate on the x-axis
   * \return Null
   *
   **/

  void PlaceSun(int y, int x);

  /**
   *
   * \brief Add the element on coordinate [x,y] inside the suns array
   * \param int y: coordinate on the y-axis
   * \param int x: coordinate on the x-axis
   * \return Null
   *
   **/

  void PlaceBox(int y, int x);

  /**
   *
   * \brief Add the player with the coordinate [x,y] and the group g
   * \param int y: coordinate on the y-axis
   * \param int x: coordinate on the x-axis
   * \param int index: index in the gameControlle map
   * \param Group * g, A pointer to the group he is in
   * \return Null
   *
   **/

  void PlacePlayer(int y, int x, int index, Group *g);

  /**
   *
   * \brief Duplicate element for the second half of the map
   * \param bool alea: if the cut is vertical(true) or horizontal(false)
   * \param int y: coordinate on the y-axis
   * \param int x: coordinate on the x-axis
   * \param int inc: number to add to have the index in the table
   * \return Null
   *
   **/

  void PlaceHalf(bool alea, int y, int x, int inc);

  /**
   *
   * \brief Duplicate element for the other quarter of the map
   * \param int y: coordinate on the y-axis
   * \param int x: coordinate on the x-axis
   * \param int inc: number to add to have the index in the table
   * \return Null
   *
   **/
  void PlaceQuarter(int y, int x, int inc);

  /**
   *
   * \brief Generate the border of the map
   * \param None
   * \return Null
   *
   **/

  void GenerateBorder();

  /**
   *
   * \brief Generate the obstacle for a part of the map
   * \param int limitH: height limit
   * \param int limitW: width limit
   * \return Null
   *
   **/

  void GenerateObstacle(int limitH, int limitW);

  /**
   *
   * \fn GenerateBox(int limitH, int limitW, int nbrBox)
   * \brief Generate the Object for a part of the map
   * \param int limitH: height limit
   * \param int limitW: width limit
   * \param int nbrBox: the number of box to generate in this part
   * \return Null
   *
   **/

  void GenerateBox(int limitH, int limitW, int nbrBox);

  /**
   *
   * \brief Generate the Sun for a part of the map
   * \param int limitH: height limit
   * \param int limitW: width limit
   * \param int nbrSun: the number of Sun to generate in this part
   * \return Null
   *
   **/

  void GenerateSun(int limitH, int limitW, int nbrSun);

  /**
   *
   * \brief Generate the Sun for a part of the map
   * \param int limitH: height limit
   * \param int limitW: width limit
   * \param int nbrPlayer: the number of Sun to generate in this part
   * \return Null
   *
   **/
  void GeneratePlayer(int limitH, int limitW, int nbrPlayer);

  /****************************** Public Method ******************************/

public:
  /****************************** Constructor ********************************/

  /**
   *
   * \brief Simplest Constructor for GameController
   * \param int = 12: The height of the map (by default 12)
   * \param int = 24: The width of the map (by default 24)
   * \return An new object GameController
   *
   * You need To call a generateMethod before using it!
   *
   **/

  Map(int = 12, int = 24);

  /**
   *
   * \brief Constructor for GameController with nbrBox and nbrSuns
   * \param int: The height of the map (by default 12)
   * \param int: The width of the map (by default 24)
   * \param int: The number of box (by default 4)
   * \return An new object GameController
   *
   * You need To call a generateMethod before using it!
   *
   **/
  Map(int, int, int);

  /******************************* Destructor ********************************/

  /**
   *
   * \brief Destructor for GameController
   * \return An new object GameController
   *
   * delete boxs and suns
   *
   **/
  ~Map();

  /********************************** Other **********************************/

  /**
   *
   * \brief Generate randomly a map without symetry
   * \param None
   * \return Null
   *
   **/

  void GenerateAllMap();

  /**
   *
   * \brief Generate randomly a map with horizontal or vertical symetry
   * \param None
   * \return Null
   *
   **/

  void GenerateHalfMap();

  /**
   *
   * \brief Generate randomly a map with horizontal & vertical symetry
   * \param None
   * \return Null
   *
   **/

  void GenerateQuarterMap();

  /**
   *
   * \brief Get the content at the [posX,posY] tile
   * \param int posY: position on the y axis
   * \param int posX: position on the x axis
   * \return the content of the tile
   *
   **/

  int GetAtIndex(int posY, int posX) const;

  /**
   *
   * \brief Set the content at the [posX,posY] tile
   * \param int posY: position on the y axis
   * \param int posX: position on the x axis
   * \param int i: The integer to add
   * \return Null
   *
   **/

  void SetAtIndex(int posY, int posX, int i);

  /**
   *
   * \brief Print the map on the terminal
   * \param None
   * \return Null
   *
   **/

  void PrintMap() const;
};

#endif
