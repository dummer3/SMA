#ifndef OBJECT_HPP
#define OBJECT_HPP

// TODO: Remove this after all object are remove
#include "Iplaceable.hpp"
class Object {
public:
  virtual void action() = 0;
  virtual ~Object();
};

class Mushroom : public Object {};

class RedShell : public IPlaceable, public Object {};

class Banana : public IPlaceable, public Object {};
// TODO: Banana action when on the map ? when use by the player ?

// TODO: Move other objects

#endif // OBJECT_HPP
