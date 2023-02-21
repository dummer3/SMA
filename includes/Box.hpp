#ifndef BOX_H
#define BOX_H

#include "Iplaceable.hpp"
#include "Object.hpp"
#include <iostream>

class Box : public IPlaceable {

private:
  Object *content;
  int cooldown;

public:
  Box(int, int);
  virtual ~Box();
  virtual void action();
  Object *GetContent();
  bool Manage();
};
#endif /* BOX_H */
