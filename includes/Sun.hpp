#ifndef SUN_H
#define SUN_H

#include "Iplaceable.hpp"
#include <iostream>

// TODO: Bouger le soleil lorsque un joueur le posséde ?

class Player;

class Sun : public IPlaceable {
public:
  Sun(int, int);
  void hitEffect(Player*);
  virtual ~Sun();
};

#endif /* SUN_H */
