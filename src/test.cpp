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

TEST_CASE("First Test") { std::cout << "Hello World" << std::endl; }

// REQUIRE();
// SECTION {}

int main(int, char **) {

  srand(time(0));

  Map m(16, 32, 1, 3);

  m.GenerateAllMap();
  m.PrintMap();
  m.GenerateHalfMap();
  m.PrintMap();
  m.GenerateQuarterMap();
  m.PrintMap();
  m.GenerateQuarterMap();
  m.PrintMap();
  return 0;
}
