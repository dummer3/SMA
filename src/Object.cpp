/**
 *
 * \file Object.cpp
 * \brief Source file for our Box class
 * \author Benquet Matthias
 * \date 31/01/2023
 *
 * For method description, see the header
 *
 **/

/*****************************************************************************/
/*                                                                           */
/*                                Include                                    */
/*                                                                           */
/*****************************************************************************/

#include "../includes/Object.hpp"
#include "../includes/Player.hpp"

/*****************************************************************************/
/*                                                                           */
/*                               Constructor                                 */
/*                                                                           */
/*****************************************************************************/
Mushroom::Mushroom() {}

RedShell::RedShell() {}

RedShell::RedShell(int y, int x, Direction direction)
    : IPlaceable(y, x, direction) {}

Banana::Banana() {}

Banana::Banana(int y, int x) : IPlaceable(y, x) {}

/*****************************************************************************/
/*                                                                           */
/*                                Destructor                                 */
/*                                                                           */
/*****************************************************************************/

Object::~Object() {}

/*****************************************************************************/
/*                                                                           */
/*                               Other Method                                */
/*                                                                           */
/*****************************************************************************/

void Mushroom::useEffect(Player* player) {
  player->setBoostTimer(3);
  player->setSpeed(2);
  delete this;
}

void Mushroom::hitEffect(Player *player) {
  // does nothing right now
}

void RedShell::useEffect(Player* player) {
  setX(player->getX());
  setY(player->getY());
  setDirection(player->getDirection());

  switch (player->getDirection()) {
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

  GameController::Get()->PlaceNewObject(this);
}

void RedShell::hitEffect(Player* player) {
  player->setBoostTimer(5);
  player->setSpeed(0);
}

void RedShell::move() {
  switch (getDirection()) {
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

void Banana::useEffect(Player *player) {
  setX(player->getX());
  setY(player->getY());

  switch (player->getDirection()) {
  case Up:
    setY(getY() - 1);
    break;
  case Down:
    setY(getY() + 1);
    break;
  case Left:
    setX(getX() + 1);
    break;
  case Right:
    setX(getX() - 1);
    break;
  }

  GameController::Get()->PlaceNewObject(this);
}

void Banana::hitEffect(Player* player) {
  player->setBoostTimer(4);
  player->setSpeed(0);
}
