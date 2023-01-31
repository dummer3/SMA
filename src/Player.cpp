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

void Player::seDeplacer(){
    
}

void Player::useObject(){
    // function of this object;
    this->_object = NULL;
}

void Player::makeDecision()
{}

