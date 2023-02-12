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
  unsigned int frame = 500000;

  srand(time(0));

  GameController *g = GameController::Get();
  g->InitGame();

  for (int i = 0; i < 100; i++) {
    g->NewRound();
    usleep(frame);
  }

  g->Destroy();
  // delete g;
  return 0;
}
