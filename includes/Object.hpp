/**
 *
 * \file Object.hpp
 * \brief Header for our Object classes
 * \author Matthias Benquet
 * \date 31/01/2023
 *
 **/

#ifndef OBJECT_HPP
#define OBJECT_HPP

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/

#include "Iplaceable.hpp"

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/

class Player;

/**
 *
 * \class Object Object.hpp "includes/Object.hpp"
 * \brief Abstract class for all objects
 *
 */
class Object {

  /******************************** Attributes ********************************/

  /********************************* Methods **********************************/
public:
  /**
   *
   * \brief action when the object is used
   * \param Player *: The player who use it
   */
  virtual void useEffect(Player *) = 0;

  /**
   *
   * \brief action when the object is hit
   * \param Player *: The player who hit it
   */
  virtual void hitEffect(Player *) = 0;

  /**
   *
   * \brief destructor of the object
   *
   */
  virtual ~Object();
};

/**
 * 
 * \class Mushroom Object.hpp "includes/Object.hpp"
 * \brief Class for the mushroom object
 * 
*/
class Mushroom : public Object {
public:
  /**
   *
   * \brief constructor of the mushroom
   *
   */
  Mushroom();

  /**
   *
   * \brief action when the mushroom is used
   * \param Player *: The player who use it
   *
   */
  void useEffect(Player *) override;

  /**
   *
   * \brief action when the Mushroom hit a Player
   * \param Player *: The player who hit it
   *
   */

  void hitEffect(Player *) override;
};

/**
 * 
 * \class RedShell Object.hpp "includes/Object.hpp"
 * \brief Class for the red shell object
 * 
*/
class RedShell : public IPlaceable, public Object {
public:
  /**
   *
   * \brief constructor of the red shell
   *
   */
  RedShell();
  RedShell(int, int, Direction);

  /**
   *
   * \brief action when the red shell is used
   * \param Player *: The player who use it
   *
   */
  void useEffect(Player *) override;

  /**
   *
   * \brief action when the red shell hit a Player
   * \param Player *: The player who hit it
   *
   */
  void hitEffect(Player *) override;

  /**
   *
   * \brief make the shell move
   *
   */
  void move();
};

/**
 * 
 * \class Banana Object.hpp "includes/Object.hpp"
 * \brief Class for the banana object
 * 
*/
class Banana : public IPlaceable, public Object {
public:
  /**
   *
   * \brief constructor of the banana
   *
   */
  Banana();

  Banana(int, int);

  /**
   *
   * \brief action when the banana is used
   * \param Player *: The player who use it
   *
   */
  void useEffect(Player *) override;

  /**
   *
   * \brief action when the banana hit a Player
   * \param Player *: The player who hit it
   *
   */
  void hitEffect(Player *) override;
};

#endif // OBJECT_HPP
