#ifndef IPLACEABLE_H
#define IPLACEABLE_H

#include <iostream>

class IPlaceable {
private:
  int y, x;

public:
  IPlaceable(int, int);
  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
};

#endif /* IPLACEABLE_H */
