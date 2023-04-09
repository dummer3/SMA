#include "../includes/Map.hpp"
#include "../includes/catch.hpp"
#include <iostream>
#include <sstream>
#include <unistd.h>

int main(int argc, char **argv) {
  unsigned int frame = 50;

  // Test if the frame gave by the user is correct
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

  // Start the game
  for (int i = 0; i < 100; i++) {
    g->NewRound();
    usleep(frame);
  }

  g->showWinner();

  // Clean Everything
  g->Destroy();
  return 0;
}
