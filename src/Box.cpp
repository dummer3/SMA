#include "../includes/Box.hpp"
#include "../includes/Player.hpp"

Box::Box(int y, int x) : IPlaceable(y, x) {}

Box::~Box()
{
  delete content;
}

Object *Box::GetContent()
{
  cooldown = 5;
  Object *cont = content;
  content = nullptr;
  return cont;
}

void Box::hitEffect(Player *player)
{
  player->setObject(GetContent());
}

bool Box::Manage()
{
  cooldown--;
  if (cooldown == 0)
  {
    generateContent();
  }
  return cooldown == 0;
}

void Box::generateContent()
{
  int random = rand() % 3;
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
