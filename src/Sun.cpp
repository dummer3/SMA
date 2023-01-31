#include "Sun.hpp"

Sun::Sun(int y, int x) : IPlaceable(y, x) {}

void Sun::action() {
  std::cout << "Sun [" << getY() << ":" << getX() << "]" << std::endl;
}

Sun::~Sun() {}
