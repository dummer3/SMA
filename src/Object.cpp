#include "../includes/Object.hpp"
#include "../includes/Player.hpp"

Object::~Object() {

}

Mushroom::Mushroom() {

}

void Mushroom::useEffect(Player* player) {
  player->setBoostTimer(3);
  player->setSpeed(2);
  delete this;
}

void Mushroom::hitEffect(Player* player) {
  
}

RedShell::RedShell() {

}

RedShell::RedShell(Direction direction) : direction(direction) {

}

void RedShell::useEffect(Player* player) {
  std::cout << "RedShell action" << std::endl;
}

void RedShell::hitEffect(Player* player) {
  player->setBoostTimer(5);
  player->setSpeed(0);
  delete this;
}

void RedShell::move() {
  switch(direction) {
    case Up:
      setY(getY() - 1);
      break;
    case Down:
      setY(getY() + 1);
      break;
    case Left:
      setX(getX() - 1);
      break;
    case Right:
      setX(getX() + 1);
      break;
  }
}

Banana::Banana() {
  
}

void Banana::useEffect(Player* player) {
  std::cout << "Banana action" << std::endl;
}

void Banana::hitEffect(Player* player) {
  player->setBoostTimer(4);
  player->setSpeed(0);
  delete this;
}
