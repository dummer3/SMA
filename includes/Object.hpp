/**
 *
 * \file Object.hpp
 * \brief Header for our Objects classes
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

// TODO: Maybe, each object is in its own file?
#include "Iplaceable.hpp"

class Player;

/*****************************************************************************/
/*                                                                           */
/*                                Class                                      */
/*                                                                           */
/*****************************************************************************/
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
     * 
     */
    virtual void useEffect(Player*) = 0;

    /**
     * 
     * \brief action when the object hit a Player
     * 
     */
    virtual void hitEffect(Player*) = 0;

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
     * 
     */
    void useEffect(Player*) override;
    void hitEffect(Player*) override;
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
     * \brief direction of the shell
     * 
    */
    Direction direction;

    /**
     * 
     * \brief constructor of the red shell
     * 
     */
    RedShell();
    RedShell(Direction);

    /**
     * 
     * \brief action when the red shell is used
     * 
     */
    void useEffect(Player*) override;

    /**
     * 
     * \brief action when the red shell hit a Player
     * 
     */
    void hitEffect(Player*) override;

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

    /**
     * 
     * \brief action when the banana is used
     * 
     */
    void useEffect(Player*) override;

    /**
     * 
     * \brief action when the banana hit a Player
     * 
     */
    void hitEffect(Player*) override;
};






// TODO: Banana action when on the map? when used by the player?

// TODO: Move other objects

#endif // OBJECT_HPP