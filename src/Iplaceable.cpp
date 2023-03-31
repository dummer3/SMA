#include "../includes/Iplaceable.hpp"

IPlaceable::IPlaceable() {};	

IPlaceable::IPlaceable(int y, int x, Direction direction) : y(y), x(x), direction(direction) {}

IPlaceable::IPlaceable(int y, int x) : y(y), x(x), direction(Up) {}

int IPlaceable::getX() const { return x; }

int IPlaceable::getY() const { return y; }

void IPlaceable::setX(int x) { this->x = x; }

void IPlaceable::setY(int y) { this->y = y; }

Direction IPlaceable::getDirection() const { return direction; }

void IPlaceable::setDirection(Direction direction) { this->direction = direction; }