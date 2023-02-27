#include "../includes/Map.hpp"
#include <iostream>
#include <sstream>
#include <unistd.h>

int main(int argc, char **argv) {
  unsigned int frame = 50;

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
  return 0;
}