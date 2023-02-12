/**
 *
 * \file Map.cpp
 * \brief Source file for our Map class
 * \author Cliquot Théo
 * \date 21/01/2023
 *
 * For method description, see the header
 *
 **/

#include "Map.hpp"

/*****************************************************************************/
/*                                                                           */
/*                               Constructor                                 */
/*                                                                           */
/*****************************************************************************/

Map::Map(int height, int width) : Map(height, width, 4) {}

Map::Map(int height, int width, int nbrBox)
    : height(height < 12 ? 12 : height), width(width < 12 ? 12 : width) {
  this->nbrBox = (nbrBox < 0) ? 0 : nbrBox;

  memset(tiles, 0, sizeof(int) * MAX_WIDTH * MAX_HEIGHT);

  InitBS();
}

/*****************************************************************************/
/*                                                                           */
/*                                Destructor */
/*                                                                           */
/*****************************************************************************/

Map::~Map() { DeleteBS(); }

/*****************************************************************************/
/*                                                                           */
/*                               Other Method                                */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*                              Private Method                               */
/*****************************************************************************/

void Map::InitBS() {
  boxs = new Box *[this->nbrBox];

  for (int b = 0; b < nbrBox; b++) {
    boxs[b] = NULL;
  }
}

void Map::DeleteBS() {
  for (int b = 0; b < nbrBox; b++)
    if (boxs[b] != NULL)
      delete boxs[b];

  delete[] boxs;
}

void Map::PlaceSun(int y, int x) {

  int tile = tiles[y][x];
  GameController::Get()->suns[tile % 100] = new Sun(y, x);
}

void Map::PlaceBox(int y, int x) {

  int tile = tiles[y][x];
  boxs[tile % 100] = new Box(y, x);
}

void Map::PlacePlayer(int y, int x, int index, Group *g) {
  GameController::Get()->players[index] = new Player(g);
  GameController::Get()->players[index]->setLocation(y, x);
}

void Map::PlaceHalf(bool alea, int y, int x, int inc) {

  int h, w;

  // If the cut is Vertical
  if (alea)
    w = width - x, h = y;

  // If the cut is Horizontal
  else
    w = x, h = height - y;

  tiles[h][w] = tiles[y][x] + inc;

  // If this element was a sun
  if (tiles[y][x] >= 1000) {
    PlaceSun(h, w);
  }
  // If it was a Box
  else if (tiles[y][x] >= 100) {
    PlaceBox(h, w);
  } else {
  }
}

void Map::PlaceQuarter(int y, int x, int inc) {
  tiles[height - y][x] =
      (tiles[y][width - x] =
           (tiles[height - y][width - x] = tiles[y][x] + inc) + inc) +
      inc;

  // If this element was a sun
  if (tiles[y][x] >= 1000) {
    PlaceSun(height - y, x);
    PlaceSun(y, width - x);
    PlaceSun(height - y, width - x);
  }
  // If it was a Box
  else if (tiles[y][x] >= 100) {
    PlaceBox(height - y, x);
    PlaceBox(y, width - x);
    PlaceBox(height - y, width - x);
  }
}

void Map::GenerateBorder() {

  // Clean the Map in case a previous map was generate
  memset(tiles, 0, sizeof(int) * MAX_WIDTH * MAX_HEIGHT);

  // Recreate our Suns and Boxs
  InitBS();

  // Horizontal Border
  for (int i = 0; i <= height; i++)
    tiles[i][0] = tiles[i][width] = -1;

  // Vertical Border
  for (int j = 0; j <= width; j++)
    tiles[0][j] = tiles[height][j] = -1;
}

void Map::GenerateObstacle(int limitH, int limitW) {

  // For every tile
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {

      // We look adjacent tiles to decide if we place an obstacle or not.
      // If adjacent tiles are obstacle, the probability to have another
      // obstacle increase.
      // like that, obstacle have better chance to form pattern.

      // Initial probability
      float proba = 0.08;

      // Adjacent tiles verification
      for (int i = -1; i <= 1; i += 2) {

        // Horizontal tiles
        if (tiles[y][i + x] == -1)
          proba += 0.14;

        // Vertical tiles
        if (tiles[y + i][x] == -1)
          proba += 0.14;
      }

      // Add or not an obstacle
      if (rand() < proba * RAND_MAX) {
        tiles[y][x] = -1;
      }
    }
  }
}

void Map::GenerateBox(int limitH, int limitW, int nbrObj) {

  // For every Box
  for (int i = 0; i < nbrObj; i++) {
    int x, y;

    // Until we find an empty tiles
    do
      y = rand() % limitH, x = rand() % limitW;
    while (tiles[y][x] != 0);

    // Add Box
    tiles[y][x] = 100 + i;
    boxs[i] = new Box(y, x);
  }
}

void Map::GenerateSun(int limitH, int limitW, int nbrSun) {

  // Add a Sun at the center of the map
  tiles[height / 2][width / 2] = 1000;
  GameController::Get()->suns[0] = new Sun(height / 2, width / 2);

  // For every Sun
  for (int i = 1; i <= nbrSun; i++) {
    int x, y;

    // Until we find an empty space
    do
      y = rand() % limitH, x = rand() % limitW;
    while (tiles[y][x] != 0);

    // Add Sun
    tiles[y][x] = 1000 + i;
    GameController::Get()->suns[i] = new Sun(y, x);
  }
}

void Map::GeneratePlayer(int limitH, int limitW, int nbrPlayer) {

  // For every Player
  for (int i = 1; i <= nbrPlayer; i++) {
    int x, y;

    // Until we find an empty space
    do
      y = rand() % limitH, x = rand() % limitW;
    while (tiles[y][x] != 0);

    // Add Player
    PlacePlayer(y, x, i, GameController::Get()->g1);
  }
}

/*****************************************************************************/
/*                               Public Method                               */
/*****************************************************************************/

void Map::GenerateAllMap() {

  // Delete previous Box and Sun
  DeleteBS();

  GenerateBorder();

  GenerateObstacle(height, width);

  GenerateBox(height, width, nbrBox);

  GenerateSun(height, width, GameController::Get()->nbrSun - 1);

  GeneratePlayer(height, width, GameController::Get()->nbrPlayer);
}

void Map::GenerateHalfMap() {

  // Delete previous Box and Sun
  DeleteBS();

  // Verification for Box
  if (nbrBox % 2 != 0) {

    // Our array is changed since the nbr was incorrect
    std::cerr << "Le nombre de Box n'est pas un multiple de 2\n"
              << "=Le nombre de Box est donc maintenant de " << ++nbrBox
              << std::endl;
  }

  // Cut Vertical (true) or horizontal(false)
  bool alea = rand() % 2 == 0;

  // Limit for our part
  int limitW = alea ? width / 2 : width;
  int limitH = alea ? height : height / 2;

  GenerateBorder();
  GenerateObstacle(limitH, limitW);

  // Apply Obstacle for other half part
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {
      if (tiles[y][x] == -1) {
        PlaceHalf(alea, y, x, 0);
      }
    }
  }

  GenerateBox(limitH, limitW, nbrBox / 2);

  // Apply Box for other half part
  int inc = nbrBox / 2;
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {
      if (tiles[y][x] >= 100) {
        PlaceHalf(alea, y, x, inc);
      }
    }
  }

  GenerateSun(limitH, limitW, (GameController::Get()->nbrSun - 1) / 2);

  // Apply Sun for other half part
  inc = (GameController::Get()->nbrSun - 1) / 2;
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {
      if (tiles[y][x] >= 1000) {
        PlaceHalf(alea, y, x, inc);
      }
    }
  }

  GameController *g = GameController::Get();
  inc = g->nbrPlayer / 2;
  GeneratePlayer(limitH, limitW, inc);

  for (int i = 1; i <= inc; i++) {
    std::pair<int, int> location = g->players[i]->getLocation();
    g->players[i + inc] =
        new Player(g->g1->SameGroup(g->players[i]->getGroup()) ? g->g2 : g->g1);
    g->players[i + inc]->setLocation(
        alea ? location.first : height - location.first,
        alea ? width - location.second : location.second);
  }
}

void Map::GenerateQuarterMap() {

  // Delete previous Box and Sun
  DeleteBS();

  // Verification for Box
  if (nbrBox % 4 != 0) {
    nbrBox += (4 - nbrBox % 4);
    std::cerr << "Le nombre de Box n'est pas un multiple de 4\n"
              << "=Le nombre de Box est donc maintenant de " << nbrBox
              << std::endl;
  }

  // Verification for Sun
  if (GameController::Get()->nbrSun % 4 != 1) {
    GameController::Get()->nbrSun += (5 - GameController::Get()->nbrSun % 4);
    std::cerr << "Le nombre de Soleil n'est pas de la forme 4*n+1\n"
              << "=Le nombre de Soleil est donc maintenant de "
              << GameController::Get()->nbrSun << std::endl;
  }

  // Limit for our part
  int limitW = width / 2;
  int limitH = height / 2;

  GenerateBorder();
  GenerateObstacle(limitH, limitW);

  // Apply Obstacle for other quarter part
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {
      if (tiles[y][x] == -1) {
        PlaceQuarter(y, x, 0);
      }
    }
  }

  GenerateBox(limitH, limitW, nbrBox / 4);

  // Apply Box for other quarter part
  int inc = nbrBox / 4;
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {
      if (tiles[y][x] >= 100) {
        PlaceQuarter(y, x, inc);
      }
    }
  }

  GenerateSun(limitH, limitW, (GameController::Get()->nbrSun - 1) / 4);

  // Apply Sun for other quarter part
  inc = (GameController::Get()->nbrSun - 1) / 4;
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {
      if (tiles[y][x] >= 1000) {
        PlaceQuarter(y, x, inc);
      }
    }
  }

  GameController *g = GameController::Get();
  inc = g->nbrPlayer / 4;
  GeneratePlayer(limitH, limitW, inc);

  for (int i = 1; i <= inc; i++) {
    std::pair<int, int> location = g->players[i]->getLocation();
    g->players[i + inc] =
        new Player(g->g1->SameGroup(g->players[i]->getGroup()) ? g->g1 : g->g2);
    g->players[i + inc]->setLocation(height - location.first,
                                     width - location.second);
    g->players[i + inc * 2] =
        new Player(g->g1->SameGroup(g->players[i]->getGroup()) ? g->g2 : g->g1);
    g->players[i + inc * 2]->setLocation(location.first,
                                         width - location.second);
    g->players[i + inc * 3] =
        new Player(g->g1->SameGroup(g->players[i]->getGroup()) ? g->g2 : g->g1);
    g->players[i + inc * 3]->setLocation(height - location.first,
                                         location.second);
  }
}

int Map::GetAtIndex(int posY, int posX) const { return tiles[posY][posX]; }

void Map::PrintMap() const {

  // For every tile
  for (int y = 0; y <= height; y++) {
    for (int x = 0; x <= width; x++) {

      // Choose the correct background colorBack
      std::string colorBack;
      std::string color;
      int tile = tiles[y][x];

      if (tile == 0)
        colorBack = COLOR_BACK_BLACK;
      else if (tile == -1)
        colorBack = COLOR_BACK_WHITE;
      else if (tile >= 1000)
        colorBack = COLOR_BACK_YELLOW;
      else
        colorBack = COLOR_BACK_BLUE;

      // choose the correct color
      Player *p = nullptr;
      for (int i = 1; i <= GameController::Get()->nbrPlayer; i++) {
        std::pair<int, int> l =
            GameController::Get()->players[i]->getLocation();
        if (y == l.first && x == l.second)
          p = GameController::Get()->players[i];
      }

      if (p) {
        if (GameController::Get()->g1->OnMyGroup(p))
          color = COLOR_MAGENTA;
        else if (GameController::Get()->g2->OnMyGroup(p))
          color = COLOR_RED;

        switch (p->getDirection()) {
        case Up:
          color += "^ ";
          break;
        case Down:
          color += "v ";
          break;
        case Left:
          color += "< ";
          break;
        case Right:
          color += "> ";
          break;
        }
      } else
        color = "  ";

      // Print it!
      std::cout << colorBack << color << COLOR_BACK_DEF << COLOR_DEF;
    }
    std::cout << std::endl;
  }

  // Place the map on the terminal correctly
  std::cout << "\033[2J";

  /*std::cout << std::endl;
  for (int s = 0; s < GameController::Get()->nbrSun; s++) {
    GameController::Get()->suns[s]->action();
  }
  std::cout << std::endl;
  for (int b = 0; b < nbrBox; b++) {
    boxs[b]->action();
  }
  std::cout << std::endl;

  for (int p = 1; p <= GameController::Get()->nbrPlayer; p++) {
    std::pair<int, int> l = GameController::Get()->players[p]->getLocation();
    std::cout << "Player[" << l.first << ":" << l.second << "]" << std::endl;
  }
  std::cout << std::endl;*/
}
