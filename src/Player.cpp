#include "Player.hpp"

Player::Player(Group *g) {
  this->_sunshine = 0;
  this->_object = NULL;
  this->_group = g;
  this->_direction = Up; // Direction up by default
  this->_speed = 0;
  this->_group->AddPlayer(this);
}

void Player::setSunshine(int numOfsunshine) { this->_sunshine = numOfsunshine; }

int Player::getSunshine(){
    return _sunshine;
}

void Player::setObject(Object * object){
    this->_object = object;
}

Object *Player::getObject() { return _object; }

void Player::setDirection(Direction direction) { this->_direction = direction; }

Direction Player::getDirection(){
    return _direction;
}

void Player::seDeplacer() { std::cout << "seDeplacer()" << std::endl; }

void Player::useObject() {
  // function of this object;
  this->_object = NULL;
}

void Player::makeDecision() {
  int interest = 0;
  int i, line;
  int deltaY = 0, deltaX = 0;
  for (int radius = 1; radius < 10 && interest < 10; radius++) {
    for (i = -1; i <= 1 && interest < 10; i += 2) {
      for (line = -radius; line <= radius && interest < 10; line++) {
        int dX = 0, dY = i,
            test = GameController::Get()->EvaluateTile(
                       _location.first + radius * i, _location.second + line) /
                   100;

        if (GameController::Get()->EvaluateTile(_location.first + line,
                                                _location.second + radius * i) /
                100 >
            test) {
          test = GameController::Get()->EvaluateTile(
                     _location.first + line, _location.second + radius * i) /
                 100;
          dY = 0;
          dX = i;
        }
        if (test > interest) {
          interest = test;
          deltaY = dY;
          deltaX = dX;
        }
      }
    }
  }
  setLocation(_location.first + deltaY, _location.second + deltaX);
}

void Player::setLocation(int y, int x) {
  _location.first = y;
  _location.second = x;
}

std::pair<int, int> Player::getLocation() const { return _location; }

const Group *Player::getGroup() const { return _group; }
