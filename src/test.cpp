#define CATCH_CONFIG_MAIN
#include "../includes/Map.hpp"
#include "../includes/catch.hpp"
#include <iostream>
#include <sstream>
#include <unistd.h>

TEST_CASE("First Test") { std::cout << "Hello World" << std::endl; }

/*********** Unit Tests ***********/
TEST_CASE("Unit_Tests") {

  SECTION("Test_of_Box") {}
  SECTION("Test_of_GameController") {}
  SECTION("Test_of_Group") {}
  SECTION("Test_of_Interface-Lace-able") {
    // This is a test for an "interface"
    // So this class cannot be instantiated
  }
  SECTION("Test_of_Map") {}
  SECTION("Test_of_Object") {
    // Juste this class can be instantiated.
  }
  SECTION("Test_of_Player") {}
  SECTION("Test_of_Sun") {}
}

/*********** Integration Tests ***********/

/*********** System Tests ***********/
TEST_CASE("System_Tests") {}
