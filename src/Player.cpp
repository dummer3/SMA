#include "../includes/Player.hpp"

Player::Player(Group *g)
{
  this->_sunshine = 0;
  this->_object = nullptr;
  this->_group = g;
  this->setDirection(Up); // Direction up by default
  this->_speed = 1;
  this->_group->AddPlayer(this);
}

Player::~Player() {
  if (this->_object != nullptr) {
    delete this->_object;
  }
}

void Player::setSunshine(int numOfsunshine) { this->_sunshine = numOfsunshine; }

int Player::getSunshine()
{
  return _sunshine;
}

void Player::setObject(Object *object)
{
  if (this->_object != nullptr)
  {
    delete this->_object;
  }
  this->_object = object;
}

Object *Player::getObject() { return _object; }

void Player::setSpeed(int speed)
{
  this->_speed = speed;
}

int Player::getSpeed()
{
  return _speed;
}

void Player::setBoostTimer(int boost_timer)
{
  this->_boost_timer = boost_timer;
}

int Player::getBoostTimer()
{
  return _boost_timer;
}

int Player::makeDecision() {
  if(this->_object != nullptr && GameController::Get()->IsThereACloseEnemyFrom(*this)) {
    useObject();
    return 1;
  } else {
    seDeplacer();
    return 2;
  }
}

void Player::useObject() {
  // function of this object;
  if (this->_object != nullptr) {
    this->_object->useEffect(this);
    this->_object = nullptr;
  }
}

void Player::seDeplacer()
{
  int interest = -1;
  int i, line;
  int deltaY = 0, deltaX = 0;
  std::pair<int, int> pos;
  pos.first = pos.second = 0;

  for (int radius = 1; radius < 10 && interest < 10; radius++)
  {
    // Watch Left and Up, then Right and Down
    for (int i = -1; i <= 1 && interest < 10; i += 2)
    {

      // Scan one side
      for (int line = -radius; line <= radius && interest < 10; line++)
      {

        std::pair<int, int> p;
        int dX = 0, dY = i;
        p.first = _location.first + radius * i;
        p.second = _location.second + line;

        // Scan Horizontaly
        int test = GameController::Get()->EvaluateTile(
                       _location.first + radius * i, _location.second + line) /
                   100;

        // Scan Vertically and keep the best one
        if (GameController::Get()->EvaluateTile(_location.first + line,
                                                _location.second + radius * i) /
                100 >
            test)
        {

          test = GameController::Get()->EvaluateTile(
                     _location.first + line, _location.second + radius * i) /
                 100;
          dY = 0;
          dX = i;
          p.first = _location.first + line,
          p.second = _location.second + radius * i;
        }

        // If it's better than the previous one.
        if (test > interest)
        {
          interest = test;
          deltaY = dY;
          deltaX = dX;
          pos = p;
        }
      }
    }
  }

  setLocation(GameController::Get()->A(_location, pos));
}

void Player::setLocation(int y, int x)
{

  _location.first = y;
  _location.second = x;
}

void Player::setLocation(std::pair<int, int> l)
{

  if (l.second < _location.second)
    setDirection(Left);
  else if (l.second > _location.second)
    setDirection(Right);
  else if (l.first < _location.first)
    setDirection(Up);
  else
    setDirection(Down);

  _location = l;
}

std::pair<int, int> Player::getLocation() const { return _location; }

const Group *Player::getGroup() const { return _group; }
