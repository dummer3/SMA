#include "Box.hpp"

Box::Box(int y, int x) : IPlaceable(y, x) {}

void Box::action() {
  std::cout << "Box [" << getY() << ":" << getX() << "]" << std::endl;
}

Box::~Box() {}
