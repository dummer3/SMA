#include "GameController.hpp"

GameController *GameController::game = nullptr;
Map *GameController::map = nullptr;

GameController::GameController(int nbrPlayer, int height, int width)
    : nbrPlayer(nbrPlayer), nbrSun(5), g1(new Group(1)), g2(new Group(2)) {

  players = new Player *[nbrPlayer + 1];
  for (int p = 1; p <= nbrPlayer; p++) {
    players[p] = nullptr;
  }

  suns = new Sun *[nbrSun];
  for (int s = 1; s < nbrSun; s++) {
    suns[s] = nullptr;
  }

  map = new Map(height, width);
}

GameController::GameController() : GameController(8, 12, 24) {}

GameController *GameController::Get(int n) {
  if (game == nullptr) {
    std::cout << "SEULEMENT UNE FOIS" << std::endl;
    game = new GameController();
  }
  return game;
}

void GameController::NewRound() {
  map->PrintMap();
  for (int i = 1; i <= nbrPlayer; i++) {
    players[i]->makeDecision();
    int result = EvaluateTile(players[i]->getLocation().first,
                              players[i]->getLocation().second);
    if (result >= 1000) {
      suns[result % 1000]->setX(-1);
      suns[result % 1000]->setY(-1);
      map->tiles[players[i]->getLocation().first]
                [players[i]->getLocation().second] = 0;
      // TODO: Give the sun to the player
    } else if (result >= 100) {
      // TODO: Give the object to the player
      map->boxs[result % 100]->GetContent();
      map->tiles[players[i]->getLocation().first]
                [players[i]->getLocation().second] = 0;
    }
  }
  for (int b = 0; b < map->nbrBox; b++) {
    if (map->boxs[b]->Manage()) {
      map->tiles[map->boxs[b]->getY()][map->boxs[b]->getX()] = 100 + b;
    }
  }
}
void GameController::InitGame() { map->GenerateQuarterMap(); }

void GameController::Destroy() {
  delete game;
  delete map;
  map = nullptr;
  game = nullptr;

  for (int p = 1; p <= nbrPlayer; p++) {
    delete players[p];
  }
  for (int s = 0; s < nbrSun; s++) {
    delete suns[s];
  }
}

int GameController::EvaluateTile(int y, int x) {
  if (y <= 0 || y >= map->height || x <= 0 || x >= map->width ||
      map->tiles[y][x] == -1) {
    return -10000;
  } else {
    return map->tiles[y][x];
  }
}
