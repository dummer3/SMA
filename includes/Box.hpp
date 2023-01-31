#ifndef BOX_H
#define BOX_H

#include "Iplaceable.hpp"
#include "Object.hpp"
#include <iostream>

class Box : public Object, public IPlaceable {

private:
  Object *content;

public:
  Box(int, int);
  virtual void action();
  virtual ~Box();
};
#endif /* BOX_H */
