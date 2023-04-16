#define CATCH_CONFIG_MAIN

#include "../includes/catch.hpp"
#include "../src/Box.cpp"
#include "../src/GameController.cpp"
#include "../src/Group.cpp"
#include "../src/Iplaceable.cpp"
#include "../src/Map.cpp"
#include "../src/Object.cpp"
#include "../src/Player.cpp"
#include "../src/Sun.cpp"

#include <iostream>
#include <sstream>
#include <unistd.h>

TEST_CASE("First Test")
{
  std::cout << "Hello World" << std::endl;
  int x = 1;
  REQUIRE(x == 1);
}

/*********** Unit Tests ***********/

TEST_CASE("Unit Test of BOX", "[Box]")
{
  Box box(2, 3);
  Player *player;
  REQUIRE(box.Manage() == true);
  box.generateContent();
  REQUIRE(box.Manage() == false);
  REQUIRE(box.getX() == 3);
  REQUIRE(box.getY() == 2);
}

TEST_CASE("Unit Test of GameController", "[GameController]")
{
  GameController *game = GameController::Get();
  REQUIRE(game != nullptr);
  // REQUIRE(game->EvaluateTile(10, 10) == 10);
  GameController *game1 = GameController::Get();
  GameController *game2 = GameController::Get();
  REQUIRE(game1 == game2);
}

TEST_CASE("Unit Test of Player", "[Player]")
{
  class TestPlayer : public Player
  {
  };
  TestPlayer *p;
  REQUIRE(p != nullptr);
}

TEST_CASE("Unit Test of Group", "[Group]")
{

  Group *group;
  Player *player;

  REQUIRE(group != nullptr);
  REQUIRE(player != nullptr);

  //(*group).AddPlayer(player);
  REQUIRE((*group).OnMyGroup(player) == false);

  Group g1(1, "My Group");
  Group g2(2, "Other Group");

  REQUIRE(g1.SameGroup(&g1) == true);
  REQUIRE(g1.SameGroup(&g2) == false);
}

/* TEST_CASE("Unit Test of Object", "[Object]")
{
  Group g;
  Player *p;
  p->setDirection(Up);
  Banana banana;
  banana.hitEffect(p);
  REQUIRE(p->getBoostTimer() == 4);
} */
