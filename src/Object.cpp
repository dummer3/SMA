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

Banana::Banana() {}

Banana::Banana(int y, int x) : IPlaceable(y, x) {}

void Banana::useEffect(Player *player) {
  Banana b(player->getY(), player->getX());

  switch (player->getDirection()) {
  case Up:
    b.setY(b.getY() - 1);
    break;
  case Down:
    b.setY(b.getY() + 1);
    break;
  case Left:
    b.setX(b.getX() + 1);
    break;
  case Right:
    b.setX(b.getX() - 1);
    break;
  }

  GameController::Get()->PlaceNewObject(&b);
}

void Banana::hitEffect(Player* player) {
  player->setBoostTimer(4);
  player->setSpeed(0);
  delete this;
}
