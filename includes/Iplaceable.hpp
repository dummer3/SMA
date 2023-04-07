/**
 *
 * \file Iplaceable.hpp
 * \brief Header for our Iplaceable Interface
 * \author Cliquot Théo
 * \date 21/01/2023
 *
 **/

#ifndef IPLACEABLE_H
#define IPLACEABLE_H

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/
#include <iostream>

/*****************************************************************************/
/*                                                                           */
/*                                 Constant                                  */
/*                                                                           */
/*****************************************************************************/

enum Direction { Up, Down, Left, Right };

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/

/**
 *
 * \class IPlaceable
 * \brief Interface for every object which can be place on the map
 *
 **/

class IPlaceable {

  /******************************* Attribute *********************************/
private:
  int y, x;
  Direction direction;

  /****************************** Public Method ******************************/
public:
  /****************************** Constructor ********************************/

  /**
   *
   * \brief Simplest Constructor for IPlaceable
   * \return Init attribute of the IPlaceable interface
   *
   **/

  IPlaceable();

  /**
   *
   * \brief Simplest Constructor for IPlaceable
   * \return Init attribute of the IPlaceable interface
   * \param int: the y-axis value
   * \param int: the x-axis value
   *
   **/

  IPlaceable(int, int);

  /**
   *
   * \brief Simplest Constructor for IPlaceable
   * \return Init attribute of the IPlaceable interface
   * \param int: the y-axis value
   * \param int: the x-axis value
   * \param Direction: the initial direction
   *
   **/

  IPlaceable(int, int, Direction);

  /******************************* Destructor ********************************/

  /**
   *
   * \brief Destructor for Map
   *
   * Abstract method
   *
   **/

  virtual ~IPlaceable() = 0;

  /********************************** Other **********************************/

  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
  Direction getDirection() const;
  void setDirection(Direction direction);
};

inline IPlaceable::~IPlaceable() {}
#endif /* IPLACEABLE_H */
