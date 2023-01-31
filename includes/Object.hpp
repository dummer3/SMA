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
     * \brief action of the object
     * 
     */
    virtual void action() = 0;

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
     * \brief action of the mushroom
     * 
     */
    void action() override;
};







/**
 * 
 * \class RedShell Object.hpp "includes/Object.hpp"
 * \brief Class for the red shell object
 * 
*/
class RedShell : public IPlaceable, public Object {};






/**
 * 
 * \class Banana Object.hpp "includes/Object.hpp"
 * \brief Class for the banana object
 * 
*/
class Banana : public IPlaceable, public Object {};






// TODO: Banana action when on the map? when used by the player?

// TODO: Move other objects

#endif // OBJECT_HPP