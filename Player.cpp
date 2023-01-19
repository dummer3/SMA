#include "Player.hpp"

Player::Player(Group g)
{
    this->_sunshine = 0;
    this->_object = NULL;
    this->_group = g;

}

void Player::setSunshine(int numOfsunshine)
{
    this->_sunshine = numOfsunshine;
}

int Player::getSunshine()
{
    return _sunshine;
}

void Player::setObject(Object object)
{
    this->_object = object;
}

Object Player::getObject()
{
    return _object;
}

void Player::seDeplacer()
{}

void Player::useObject()
{
    // function of this object;
    this->_object = NULL;
}

void Player::makeDecision()
{}

void Player::makeDecision()
{}