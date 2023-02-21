#define CATCH_CONFIG_MAIN
#include <iostream>
#include "Map.hpp"
#include "catch.hpp"
#include <sstream>
#include <unistd.h>

TEST_CASE("First Test") {
    std::cout << "Hello World" << std::endl;
}

/*********** Unit Tests ***********/
TEST_CASE("Unit_Tests") {


    SECTION("Test_of_Box") {

    }
    SECTION("Test_of_GameController"){}
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
TEST_CASE("Integration_Tests") {
    unsigned int frame = 50;
    int argc = 2; // It`s just a demo for the test.
    char * argv = "Hello"; // No idea with the input for this param. !!!

    if (argc > 1) {
        std::istringstream ss(argv[1]);
        if (!(ss >> frame)) {
            std::cerr << "Invalid number: " << argv[1] << '\n';
        } else if (!ss.eof()) {
            std::cerr << "Trailing characters after number: " << argv[1] << '\n';
        }
    }

    frame *= 10000;
    srand(time(0));

    GameController *g = GameController::Get();
    g->InitGame();

    for (int i = 0; i < 100; i++) {
        g->NewRound();
        usleep(frame);
    }

    g->Destroy();
    // delete g;
}
/*********** System Tests ***********/
TEST_CASE("System_Tests") {}
