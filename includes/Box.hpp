/**
 *
 * \file Box.hpp
 * \brief Header for our Box class
 * \author Benquet Matthias
 * \date 21/01/2023
 *
 **/

#ifndef BOX_H
#define BOX_H

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/

#include "Iplaceable.hpp"
#include "Object.hpp"
#include <iostream>

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/

/**
 *
 * \class Box
 * \brief The Box is an object factory
 *
 * Implement the IPlaceable interface
 *
 **/

class Box : public IPlaceable {

private:
  /******************************* Attribute *********************************/
  Object *content;
  int cooldown = 1;

public:
  /****************************** Public Method ******************************/
  /****************************** Constructor ********************************/

  /**
   *
   * \brief Constructor for Box
   * \param int: The value for the y axis
   * \param int: The value for the x axis
   * \return An new object Box
   *
   **/
  Box(int, int);

  /******************************* Destructor ********************************/

  /**
   *
   * \brief Destructor for Box
   *
   **/
  virtual ~Box();

  /********************************** Other **********************************/

  /**
   *
   * \fn virtual void hitEffect(Player *);
   * \brief Give a object to the player who hit
   * \param Player*: The player who hit the box
   * \return Null
   *
   **/

  virtual void hitEffect(Player *);

  /**
   *
   * \fn Object *GetContent();
   * \brief Give the object store in the box, start the cooldown
   * \param None
   * \return Object*: The object inside the box
   *
   **/

  Object *GetContent();

  /**
   *
   * \fn bool Manage();
   * \brief Return true if the box just create an object
   * \param None
   * \return bool: if an object is create
   *
   **/

  bool Manage();

  /**
   *
   * \fn void generateContent();
   * \brief create a new Object
   * \param None
   * \return Null
   *
   **/
  void generateContent();
};
#endif /* BOX_H */
