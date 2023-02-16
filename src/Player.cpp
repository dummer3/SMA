#include "Player.hpp"

Player::Player(Group g){
    this->_sunshine = 0;
    this->_object = NULL;
    this->_group = g;
    this->_direction = Up; // Direction up by default
    this->_speed = 0;
}

void Player::setSunshine(int numOfsunshine){
    this->_sunshine = numOfsunshine;
}

int Player::getSunshine(){
    return _sunshine;
}

void Player::setObject(Object * object){
    this->_object = object;
}

Object * Player::getObject(){
    return _object;
}

void Player::setDirection(Direction direction){
    this->_direction = direction;
}

Direction Player::getDirection(){
    return _direction;
}

void Player::setSpeed(int speed){
    this->_speed = speed;
}

int Player::getSpeed(){
    return _speed;
}

void Player::setBoostTimer(int boost_timer){
    this->_boost_timer = boost_timer;
}

int Player::getBoostTimer(){
    return _boost_timer;
}

void Player::seDeplacer(){
    std::cout << "seDeplacer()" << std::endl;
}

void Player::useObject(){
    // function of this object;
    if (this->_object != nullptr) {
        this->_object->useEffect(this);
        this->_object = nullptr; // nullptr or delete _object ?
    }
}

void Player::makeDecision() {
    std::cout << "makeDecision()" << std::endl;
}

