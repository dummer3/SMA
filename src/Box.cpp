#include "../includes/Box.hpp"
#include "../includes/Player.hpp"

Box::Box(int y, int x) : IPlaceable(y, x) {}

Object *Box::GetContent() {
  cooldown = 5;
  Object* cont = content;
  content = nullptr;
  return cont;
}

void Box::hitEffect(Player* player) {
  player->setObject(content);
  content = nullptr;
}

bool Box::Manage() {
  int random = rand() % 3;
  cooldown--;
  if (cooldown == 0) {
    switch (random)
    {
    case 0:
      content = new Mushroom();
      break;
    case 1:
      content = new RedShell();
      break;
    case 2:
      content = new Banana();
      break;
    }
  }
  return cooldown == 0;
}

Box::~Box() {
  delete content;
}
