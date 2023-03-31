#ifndef IPLACEABLE_H
#define IPLACEABLE_H

#include <iostream>
enum Direction { Up, Down, Left, Right };

class IPlaceable {
private:
  int y, x;
  Direction direction;

public:
  IPlaceable();
  IPlaceable(int, int, Direction);
  IPlaceable(int, int);
  virtual ~IPlaceable() = 0;
  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
  Direction getDirection() const;
  void setDirection(Direction direction);

};

inline IPlaceable::~IPlaceable() {}

#endif /* IPLACEABLE_H */
