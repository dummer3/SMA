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
  delete map;
  map = nullptr;

  delete g1;
  delete g2;

  for (int p = 1; p <= nbrPlayer; p++) {
    delete players[p];
  }
  delete players;

  for (int s = 0; s < nbrSun; s++) {
    delete suns[s];
  }
  delete suns;

  delete game;
  game = nullptr;
}

int GameController::EvaluateTile(int y, int x) {
  if (y <= 0 || y >= map->height || x <= 0 || x >= map->width ||
      map->tiles[y][x] == -1) {
    return -10000;
  } else {
    return map->tiles[y][x];
  }
}

int dist(std::pair<int, int> start, std::pair<int, int> end) {
  return std::abs(start.first - end.first) +
         std::abs(start.second - end.second);
}

std::pair<int, int> GameController::A(std::pair<int, int> start,
                                      std::pair<int, int> end) {

  class Content {
  public:
    std::pair<int, int> position;
    int weight;
    int prediction;
    std::pair<int, int> parent;

    Content(std::pair<int, int> p = {-1, -1}, int w = 0, int h = 0,
            std::pair<int, int> parent = {-1, -1})
        : position(p), weight(w), prediction(h), parent(parent){};

    bool operator<(const Content &other) const { return weight < other.weight; }
    bool operator<=(const Content &other) const {
      return weight <= other.weight;
    }
    bool operator==(const Content &other) const {
      return position == other.position;
    }
  };

  class comparator {
  public:
    bool operator()(const Content &c1, const Content &c2) const {
      return c2.prediction <= c1.prediction;
    }
  };

  p_queue<Content, std::vector<Content>, comparator> openList;
  openList.push(Content{start, 0, 0, {-1, -1}});

  f_stack<Content> closedList;

  auto helloNeighbor = [end, &closedList, &openList](
                           Content &actual, std::pair<int, int> ngh_pos) {
    std::pair<int, int> act_pos = actual.position;

    if (ngh_pos.second < map->width && ngh_pos.second > 0 &&
        ngh_pos.first < map->height && ngh_pos.first > 0 &&
        map->tiles[ngh_pos.first][ngh_pos.second] != -1) {

      Content neighbor(ngh_pos, actual.weight + 1,
                       actual.weight + 1 + dist(ngh_pos, end), act_pos);

      if (!(closedList.find(neighbor) || openList.find(neighbor))) {
        openList.push(neighbor);
      }
    }
  };

  /*std::cout << "Start "
            << "[" << start.first << ":" << start.second << "] "
            << "End "
            << "[" << end.first << ":" << end.second << "] " << std::endl;*/

  bool find = false;

  while (!openList.empty() && !find) {
    Content actual = openList.top();
    openList.pop();

    /*std::cout << "NEW TILE "
              << "[" << actual.position.first << ":" << actual.position.second
              << "] " << std::endl;*/

    if (actual.position == end) {
      // std::cout << "END ATTEINT " << std::endl;
      std::pair<int, int> parent = actual.parent;
      while (parent != start) {
        do {
          actual = closedList.top();
          closedList.pop();
        } while (actual.position != parent);
        parent = actual.parent;
      }
      return actual.position;
    } else {

      // for each near nodes
      helloNeighbor(actual,
                    {actual.position.first, actual.position.second - 1});
      helloNeighbor(actual,
                    {actual.position.first, actual.position.second + 1});
      helloNeighbor(actual,
                    {actual.position.first - 1, actual.position.second});
      helloNeighbor(actual,
                    {actual.position.first + 1, actual.position.second});
      closedList.push(actual);
    }
  }
  std::cerr << "Objectif non accessible ?!!" << std::endl;
  exit(1);
}
