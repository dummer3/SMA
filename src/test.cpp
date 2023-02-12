/*
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

TEST_CASE("First Test") {
    std::cout << "Hello World" << std::endl;
}

// REQUIRE();
// SECTION {}*/

#include "Map.hpp"
#include "catch.hpp"
#include <iostream>
#include <unistd.h>

int main(int, char **) {

  srand(time(0));

  GameController *g = GameController::Get();
  g->InitGame();

  for (int i = 0; i < 100; i++) {
    g->NewRound();
    sleep(1);
  }

  g->Destroy();
  // delete g;
  return 0;
}
