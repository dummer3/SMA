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

Map::Map(int height, int width) : Map(height, width, 4, 5) {}

Map::Map(int height, int width, int nbrBox, int nbrSun)
    : height(height < 12 ? 12 : height), width(width < 12 ? 12 : width) {
  this->nbrBox = (nbrBox < 0) ? 0 : nbrBox;
  this->nbrSun = (nbrSun < 1) ? 1 : (nbrSun % 2 == 1) ? nbrSun : ++nbrSun;

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
  suns = new Sun *[this->nbrSun];
  boxs = new Box *[this->nbrBox];

  for (int b = 0; b < nbrBox; b++) {
    boxs[b] = NULL;
  }
  for (int s = 0; s < nbrSun; s++) {
    suns[s] = NULL;
  }
}

void Map::DeleteBS() {
  for (int s = 0; s < nbrSun; s++)
    if (suns[s] != NULL)
      delete suns[s];

  delete[] suns;

  for (int b = 0; b < nbrBox; b++)
    if (boxs[b] != NULL)
      delete boxs[b];

  delete[] boxs;
}

void Map::PlaceSun(int y, int x) {

  int tile = tiles[y][x];
  suns[tile % 100] = new Sun(y, x);
}

void Map::PlaceBox(int y, int x) {

  int tile = tiles[y][x];
  boxs[tile % 100] = new Box(y, x);
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

      // Initial probabilty
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
  suns[0] = new Sun(height / 2, width / 2);

  // For every Sun
  for (int i = 1; i <= nbrSun; i++) {
    int x, y;

    // Until we find an empty space
    do
      y = rand() % limitH, x = rand() % limitW;
    while (tiles[y][x] != 0);

    // Add Sun
    tiles[y][x] = 1000 + i;
    suns[i] = new Sun(y, x);
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

  GenerateSun(height, width, nbrSun - 1);
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

  GenerateSun(limitH, limitW, (nbrSun - 1) / 2);

  // Apply Sun for other half part
  inc = (nbrSun - 1) / 2;
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {
      if (tiles[y][x] >= 1000) {
        PlaceHalf(alea, y, x, inc);
      }
    }
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
  if (nbrSun % 4 != 1) {
    nbrSun += (5 - nbrSun % 4);
    std::cerr << "Le nombre de Soleil n'est pas de la forme 4*n+1\n"
              << "=Le nombre de Soleil est donc maintenant de " << nbrSun
              << std::endl;
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

  GenerateSun(limitH, limitW, (nbrSun - 1) / 4);

  // Apply Sun for other quarter part
  inc = (nbrSun - 1) / 4;
  for (int y = 1; y < limitH; y++) {
    for (int x = 1; x < limitW; x++) {
      if (tiles[y][x] >= 1000) {
        PlaceQuarter(y, x, inc);
      }
    }
  }
}

void Map::PrintMap() const {

  // For every tile
  for (int y = 0; y <= height; y++) {
    for (int x = 0; x <= width; x++) {

      // Choose the correct color
      std::string color;
      int tile = tiles[y][x];

      if (tile == 0)
        color = COLOR_BLACK;
      else if (tile == -1)
        color = COLOR_WHITE;
      else if (tile >= 1000)
        color = COLOR_YELLOW;
      else
        color = COLOR_BLUE;

      // Print it;
      std::cout << color << std::setw(3) << "" << COLOR_DEF;
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  for (int s = 0; s < nbrSun; s++) {
    suns[s]->action();
  }
  std::cout << std::endl;
  for (int b = 0; b < nbrBox; b++) {
    boxs[b]->action();
  }
  std::cout << std::endl;
}
