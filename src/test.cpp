#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

TEST_CASE("First Test") {
    std::cout << "Hello World" << std::endl;
}

// REQUIRE();
// SECTION {}