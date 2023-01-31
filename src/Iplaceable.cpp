#include "Iplaceable.hpp"

int IPlaceable::getX() const { return x; }

int IPlaceable::getY() const { return y; }

void IPlaceable::setX(int x) { this->x = x; }

void IPlaceable::setY(int y) { this->y = y; }

IPlaceable::IPlaceable(int y, int x) : y(y), x(x){};
