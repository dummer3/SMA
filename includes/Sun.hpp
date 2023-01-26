#ifndef SUN_H
#define SUN_H

#include "Iplaceable.hpp"
#include "Object.hpp"
#include <iostream>

// TODO: Bouger le soleil lorsque un joueur le posséde ?

class Sun : public Object, public IPlaceable {
public:
  Sun(int, int);
  virtual void action();
  virtual ~Sun();
};

#endif /* SUN_H */
