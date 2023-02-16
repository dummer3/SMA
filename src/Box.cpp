#include "Box.hpp"

Box::Box(int y, int x) : IPlaceable(y, x) {}

Object *Box::GetContent() {
  cooldown = 5;
  return content;
}

void Box::action() {
  std::cout << "Box [" << getY() << ":" << getX() << "]" << std::endl;
}

bool Box::Manage() {
  cooldown--;
  if (cooldown == 0) {
    content = new Mushroom();
  }
  return cooldown == 0;
}

Box::~Box() {}
