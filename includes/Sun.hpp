/**
 *
 * \file Sun.hpp
 * \brief Header for our Sun class
 * \author Benquet Matthias
 * \date 21/01/2023
 *
 **/

#ifndef SUN_H
#define SUN_H

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/

#include "Iplaceable.hpp"
#include <iostream>

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/

class Player;

/**
 *
 * \class Sun
 * \brief The Sun is the objectif for the player
 *
 * Implement the IPlaceable interface
 *
 **/

class Sun : public IPlaceable {
public:
  /****************************** Public Method ******************************/
  /****************************** Constructor ********************************/

  /**
   *
   * \brief Constructor for Sun
   * \param int: The value for the y axis
   * \param int: The value for the x axis
   * \return An new object Sun
   *
   **/

  Sun(int, int);
  /******************************* Destructor ********************************/

  /**
   *
   * \brief Destructor for Box
   *
   **/
  virtual ~Sun();
  /********************************** Other **********************************/

  /**
   *
   * \fn virtual void hitEffect(Player *);
   * \brief Give a Sun to the player who hit
   * \param Player*: The player who hit the box
   * \return Null
   *
   **/
  void hitEffect(Player *);
};

#endif /* SUN_H */
