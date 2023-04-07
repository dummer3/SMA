/**
 *
 * \file GameController.cpp
 * \brief Source Code for our GameController class
 * \author Cliquot Théo, Benquet Matthias
 * \date 12/02/2023
 *
 * For method description, see the header
 *
 **/

#include "../includes/GameController.hpp"
#include "../includes/Object.hpp"
#include <typeinfo>

/******************************** Initializer *********************************/

GameController *GameController::game = nullptr;
Map *GameController::map = nullptr;

/*****************************************************************************/
/*                                                                           */
/*                               Constructor                                 */
/*                                                                           */
/*****************************************************************************/

GameController::GameController(int nbrPlayer, int height, int width)
    : nbrPlayer(nbrPlayer), nbrSun(5), g1(new Group(1)), g2(new Group(2)) {

  // Create players
  players = new Player *[nbrPlayer + 1];
  for (int p = 1; p <= nbrPlayer; p++) {
    players[p] = nullptr;
  }

  // Create Suns
  suns = new Sun *[nbrSun];
  for (int s = 1; s < nbrSun; s++) {
    suns[s] = nullptr;
  }

  // Create Objects
  objects = new IPlaceable *[80];
  for (int s = 1; s < 80; s++) {
    objects[s] = nullptr;
  }

  map = new Map(height, width);
}

GameController::GameController() : GameController(8, 12, 24) {}

/*****************************************************************************/
/*                               Public Method                               */
/*****************************************************************************/

GameController *GameController::Get(int n) {
  // if no GameController exist
  if (game == nullptr) {
    // Create one
    std::cout << "SEULEMENT UNE FOIS" << std::endl;
    game = new GameController();
  }
  return game;
}

void GameController::NewRound() {
  // print the current position
  map->PrintMap();

  ManagePlayers();
  ManageBoxes();
  ManageObjects();
}

void GameController::ManagePlayers() {
  // for each players
  for (int i = 1; i <= nbrPlayer; i++) {
    // how many times our player play (mushroom)
    for (int j = 0; j < players[i]->getSpeed(); j++) {

      // Player move or use a object
      players[i]->makeDecision();

      // See where our player finish
      int result = map->tiles[players[i]->getLocation().first]
                             [players[i]->getLocation().second];

      // If he's on a sun
      if (result >= 1000) {

        // Remove the sun from the map
        suns[result % 1000]->setX(-1);
        suns[result % 1000]->setY(-1);
        map->tiles[players[i]->getLocation().first]
                  [players[i]->getLocation().second] = 0;

        // Give the sun to the player
        suns[result % 1000]->hitEffect(players[i]);
      }
      // Finish on a box
      else if (result >= 100) {

        // Give the object to the player
        map->boxs[result % 100]->hitEffect(players[i]);
        map->tiles[players[i]->getLocation().first]
                  [players[i]->getLocation().second] = 0;
      }
    }
    // Decrement the boost timer
    players[i]->setBoostTimer(players[i]->getBoostTimer() - 1);
    if (players[i]->getBoostTimer() == 0) {
      players[i]->setSpeed(1);
    }
  }
}

void GameController::ManageBoxes() {
  // For each box
  for (int b = 0; b < map->nbrBox; b++) {
    // If the box create a object
    if (map->boxs[b]->Manage()) {
      // Put it on the map
      map->tiles[map->boxs[b]->getY()][map->boxs[b]->getX()] = 100 + b;
    }
  }
}

void GameController::ManageObjects() {

  // For each objects
  for (int o = 1; o < 80; o++) {
    if (objects[o] != nullptr) // check if object exists
    {
      // if o is a shell make it move
      if (typeid(*(objects[o])).name() == typeid(RedShell).name()) {
        RedShell *rs = dynamic_cast<RedShell *>(objects[o]);
        rs->move();

        // Check if the shell hit a wall
        if (map->tiles[rs->getY()][rs->getX()] == -1) {
          delete objects[o];
          objects[o] = nullptr;
          break;
        }
      }
      // If object hit player, player lose sun and hitEffect
      for (int p = 1; p <= nbrPlayer; p++) {
        Object *ob = dynamic_cast<Object *>(objects[o]);
        if (objects[o]->getX() == players[p]->getX() &&
            objects[o]->getY() == players[p]->getY()) {
          loseSun(players[p]);
          ob->hitEffect(players[p]);
          delete objects[o];
          objects[o] = nullptr;
          break;
        }
      }
    }
  }
}

// By default, it's a quarterMap
void GameController::InitGame() { map->GenerateQuarterMap(); }

int GameController::EvaluateTile(int y, int x) {
  // Give a bad score to unapproachable tile
  if (y <= 0 || y >= map->height || x <= 0 || x >= map->width ||
      map->tiles[y][x] == -1 || GameController::Get()->PlayerHere({y, x})) {
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
  // Class to save pathfinding information
  class Content {
  public:
    std::pair<int, int> position; // position (y & x axis)
    int weight;                   // the actual cost
    int prediction;               // prediction to go to the end
    std::pair<int, int> parent;   // the tile before

    // Constructor
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

  // Functor to compare two content on our priority_queue
  class comparator {
  public:
    bool operator()(const Content &c1, const Content &c2) const {
      return c2.prediction < c1.prediction;
    }
  };

  // List of tile we have to analyse
  p_queue<Content, std::vector<Content>, comparator> openList;
  openList.push(Content{start, 0, dist(start, end), {-1, -1}});

  // File of tile we had analyse
  f_stack<Content> closedList;

  // The closest tiles we find
  Content closest{start, 0, dist(start, end) * 100, {-1, -1}};

  // function to analyse adjacent tiles
  auto helloNeighbor = [end, &closedList, &openList, &closest](
                           Content &actual, std::pair<int, int> ngh_pos) {
    std::pair<int, int> act_pos = actual.position;

    // Look if the tiles is empty
    if (ngh_pos.second < map->width && ngh_pos.second > 0 &&
        ngh_pos.first < map->height && ngh_pos.first > 0 &&
        map->tiles[ngh_pos.first][ngh_pos.second] != -1 &&
        !GameController::Get()->PlayerHere(ngh_pos)) {

      // Create the content associate to this tiles
      Content neighbor(ngh_pos, actual.weight + 1,
                       actual.weight + 1 + dist(ngh_pos, end), act_pos);

      // If this tiles is interesting, we save it.
      if (!(closedList.find(neighbor) || openList.find(neighbor))) {
        openList.push(neighbor);

        // If it's the best actual tiles , we save it
        if (dist(end, neighbor.position) + neighbor.weight < closest.prediction)
          closest = {neighbor.position, neighbor.weight,
                     dist(end, neighbor.position) + neighbor.weight,
                     neighbor.parent};
      }
    }
  };

  // While we have tiles to analyse
  while (!openList.empty()) {

    Content actual = openList.top();
    openList.pop();

    // If we find the objectif
    if (actual.position == end) {

      // We must find now the first tile to take
      std::pair<int, int> parent = actual.parent;

      while (parent != start) {
        do {
          actual = closedList.top();
          closedList.pop();
        } while (actual.position != parent);
        parent = actual.parent;
      }

      return actual.position;
    }
    // Else, we continue our search
    else {

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

  // If we can't even move from the start
  if (closest.parent.first == -1)
    return start;

  // In this case, we can't go to the end tile, so we choose to follow the
  // closest tile instead

  std::pair<int, int> parent = closest.parent;
  while (parent != start) {
    do {
      closest = closedList.top();
      closedList.pop();
    } while (closest.position != parent);
    parent = closest.parent;
  }
  return closest.position;
}

void GameController::loseSun(Player *player) {

  // If the player has at least one sun
  if (player->getSunshine() > 0) {

    player->setSunshine(player->getSunshine() - 1);
    std::pair<int, int> posSun = findFreeTile(player);
    int s = 0;
    bool found = false;

    // find first sun in -1,-1
    while (!found) {
      if ((suns[s]->getX() == -1 && suns[s]->getY() == -1) || s == nbrSun) {
        found = true;
      } else {
        s++;
      }
    }

    if (s == nbrSun) {
      std::cerr << "No more sun available" << std::endl;
      exit(1);
    } else { // Place the sun on the map
      suns[s]->setX(posSun.first);
      suns[s]->setY(posSun.second);
      map->tiles[posSun.first][posSun.second] = 1000 + s;
    }
  }
}

std::pair<int, int> GameController::findFreeTile(Player *player) {

  std::pair<int, int> pos = player->getLocation();
  std::pair<int, int> posSun = pos;

  // look at the adjacent tiles and take the first free
  for (int i = pos.first - 2; i < pos.first + 2; i++) {
    for (int j = pos.second - 2; j < pos.second + 2; j++) {
      if (EvaluateTile(i, j) == 0 && i != pos.first && j != pos.second) {
        posSun.first = i;
        posSun.second = j;
      }
    }
  }

  return posSun;
}

bool GameController::PlayerHere(std::pair<int, int> loc) {
  for (int p = 1; p <= nbrPlayer; p++) {
    if (players[p]->getLocation() == loc)
      return true;
  }

  return false;
}

void GameController::PlaceNewObject(IPlaceable *o) {
  // If it's not a wall
  if (map->GetAtIndex(o->getY(), o->getX()) != -1) {
    int index = 0;
    for (int i = 1; i < 80; i++) {
      if (objects[i] == nullptr) {
        index = i;
        break;
      }
    }
    // Put the object on the map
    objects[index] = o;
    map->SetAtIndex(o->getY(), o->getX(), 10 + index);
  } else {
    delete o;
  }
}

bool GameController::IsThereACloseEnemyFrom(const Player& player) {
  std::pair<int, int> currentEnemyLoc;
  std::pair<int, int> playerLoc = player.getLocation();
  bool found = false;
  int p;
  for (p = 1; p <= nbrPlayer && !found; p++) {
    if (players[p]->getGroup() != player.getGroup()) {
      currentEnemyLoc = players[p]->getLocation();
      switch(player.getDirection()) {
        case Left:
          if (currentEnemyLoc.first == playerLoc.first &&
              playerLoc.second - currentEnemyLoc.second <= 4 && playerLoc.second - currentEnemyLoc.second > 0) {
                found = true;
              }
          break;
        case Right:
          if (currentEnemyLoc.first == playerLoc.first &&
              currentEnemyLoc.second - playerLoc.second <= 4 && currentEnemyLoc.second - playerLoc.second > 0) {
                found = true;
              }
          break;
        case Up:
          if (currentEnemyLoc.second == playerLoc.second &&
              playerLoc.first - currentEnemyLoc.first <= 4 && playerLoc.first - currentEnemyLoc.first > 0) {
                found = true;
              }
          break;
        case Down:
          if (currentEnemyLoc.second == playerLoc.second &&
              currentEnemyLoc.first - playerLoc.first <= 4 && currentEnemyLoc.first - playerLoc.first > 0) {
                found = true;
              }
          break;
      }
    }
  }
  return found;
}

/*****************************************************************************/
/*                                                                           */
/*                                Destructor                                 */
/*                                                                           */
/*****************************************************************************/

void GameController::Destroy() {
  // Remove map
  delete map;
  map = nullptr;

  delete g1;
  delete g2;

  // Remove players
  for (int p = 1; p <= nbrPlayer; p++) {
    delete players[p];
  }
  delete[] players;

  // Remove suns
  for (int s = 0; s < nbrSun; s++) {
    delete suns[s];
  }
  delete[] suns;

  // Remove objects
  for (int o = 1; o < 80; o++) {
    delete objects[o];
  }
  delete[] objects;

  // Remove our GameController instance
  delete game;
  game = nullptr;
}
