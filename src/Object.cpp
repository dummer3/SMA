#include "Object.hpp"
#include "Player.hpp"

Object::~Object() {

}

Mushroom::Mushroom() {

}

void Mushroom::useEffect(Player* player) {
  std::cout << "Mushroom action" << std::endl;
  player->setBoostTimer(3);
  player->setSpeed(2);
}

void Mushroom::hitEffect(Player* player) {
  
}

RedShell::RedShell() {

}

void RedShell::useEffect(Player* player) {
  std::cout << "RedShell action" << std::endl;
}

void RedShell::hitEffect(Player* player) {
  std::cout << "RedShell hit" << std::endl;
}

Banana::Banana() {

}

void Banana::useEffect(Player* player) {
  std::cout << "Banana action" << std::endl;
}

void Banana::hitEffect(Player* player) {
  std::cout << "Banana hit" << std::endl;
}
