#ifndef BOX_H
#define BOX_H

#include "Iplaceable.hpp"
#include "Object.hpp"
#include <iostream>

class Box : public IPlaceable {

private:
  Object *content;
  int cooldown = 1;

public:
  Box(int, int);
  virtual ~Box();
  virtual void hitEffect(Player*);
  Object *GetContent();
  bool Manage();
};
#endif /* BOX_H */
