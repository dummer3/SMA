#include "../includes/GameController.hpp"
#include <typeinfo>
#include "../includes/Object.hpp"


GameController *GameController::game = nullptr;

Map *GameController::map = nullptr;

GameController::GameController(int nbrPlayer, int height, int width)
    : nbrPlayer(nbrPlayer), nbrSun(5), g1(new Group(1)), g2(new Group(2))
{

  players = new Player *[nbrPlayer + 1];
  for (int p = 1; p <= nbrPlayer; p++)
  {
    players[p] = nullptr;
  }

  suns = new Sun *[nbrSun];
  for (int s = 1; s < nbrSun; s++)
  {
    suns[s] = nullptr;
  }

  objects = new IPlaceable *[80];
  for (int s = 1; s < 80; s++)
  {
    objects[s] = nullptr;
  }

  map = new Map(height, width);
}

GameController::GameController() : GameController(8, 12, 24) {}

GameController *GameController::Get(int n)
{
  if (game == nullptr)
  {
    std::cout << "SEULEMENT UNE FOIS" << std::endl;
    game = new GameController();
  }
  return game;
}

void GameController::NewRound()
{
  map->PrintMap();
  
  ManagePlayers();

  ManageBoxes();

  ManageObjects();
}

void GameController::ManagePlayers() {
  for (int i = 1; i <= nbrPlayer; i++)
  {
    players[i]->makeDecision();
    int result = map->tiles[players[i]->getLocation().first]
                           [players[i]->getLocation().second];
    if (result >= 1000)
    {
      suns[result % 1000]->setX(-1);
      suns[result % 1000]->setY(-1);
      map->tiles[players[i]->getLocation().first]
                [players[i]->getLocation().second] = 0;
      // Give the sun to the player
      suns[result % 1000]->hitEffect(players[i]);
    }
    else if (result >= 100)
    {
      // Give the object to the player
      map->boxs[result % 100]->hitEffect(players[i]);
      map->tiles[players[i]->getLocation().first]
                [players[i]->getLocation().second] = 0;
    }
  }
}

void GameController::ManageBoxes()
{
  for (int b = 0; b < map->nbrBox; b++)
  {
    if (map->boxs[b]->Manage())
    {
      map->tiles[map->boxs[b]->getY()][map->boxs[b]->getX()] = 100 + b;
    }
  }
}

void GameController::ManageObjects() {
  for (int o = 1; o < 80; o++)
  {
    if (objects[o] != nullptr) // check if object exists
    {
      // if o is a shell make it move
      if (typeid(*(objects[o])).name() == typeid(RedShell).name())
      {
        RedShell *rs = dynamic_cast<RedShell *>(objects[o]);
        rs->move();
        // check if the shell hit a wall
        if (map->tiles[rs->getY()][rs->getX()] == 1)
        {
          delete objects[o];
          objects[o] = nullptr;
        }
      }
      // if object hit player, player lose sun and hitEffect
      for (int p = 1; p <= nbrPlayer; p++)
      {
        Object *ob = dynamic_cast<Object *>(objects[o]);
        if (objects[o]->getX() == players[p]->getX() && objects[o]->getY() == players[p]->getY())
        {
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

void GameController::InitGame() { map->GenerateQuarterMap(); }

void GameController::Destroy()
{
  delete map;
  map = nullptr;

  delete g1;
  delete g2;

  for (int p = 1; p <= nbrPlayer; p++)
  {
    delete players[p];
  }
  delete[] players;

  for (int s = 0; s < nbrSun; s++)
  {
    delete suns[s];
  }
  delete[] suns;

  for (int o = 1; o < 80; o++)
  {
    delete objects[o];
  }
  delete[] objects;

  delete game;
  game = nullptr;
}

int GameController::EvaluateTile(int y, int x)
{
  if (y <= 0 || y >= map->height || x <= 0 || x >= map->width ||
      map->tiles[y][x] == -1 || GameController::Get()->PlayerHere({y, x}))
  {
    return -10000;
  }
  else
  {
    return map->tiles[y][x];
  }
}

int dist(std::pair<int, int> start, std::pair<int, int> end)
{
  return std::abs(start.first - end.first) +
         std::abs(start.second - end.second);
}

std::pair<int, int> GameController::A(std::pair<int, int> start,
                                      std::pair<int, int> end)
{

  class Content
  {
  public:
    std::pair<int, int> position;
    int weight;
    int prediction;
    std::pair<int, int> parent;

    Content(std::pair<int, int> p = {-1, -1}, int w = 0, int h = 0,
            std::pair<int, int> parent = {-1, -1})
        : position(p), weight(w), prediction(h), parent(parent){};

    bool operator<(const Content &other) const { return weight < other.weight; }
    bool operator<=(const Content &other) const
    {
      return weight <= other.weight;
    }
    bool operator==(const Content &other) const
    {
      return position == other.position;
    }
  };

  class comparator
  {
  public:
    bool operator()(const Content &c1, const Content &c2) const
    {
      return c2.prediction < c1.prediction;
    }
  };

  p_queue<Content, std::vector<Content>, comparator> openList;
  openList.push(Content{start, 0, dist(start, end), {-1, -1}});

  f_stack<Content> closedList;

  Content closest{start, 0, dist(start, end) * 100, {-1, -1}};

  auto helloNeighbor = [end, &closedList, &openList, &closest](
                           Content &actual, std::pair<int, int> ngh_pos)
  {
    std::pair<int, int> act_pos = actual.position;

    if (ngh_pos.second < map->width && ngh_pos.second > 0 &&
        ngh_pos.first < map->height && ngh_pos.first > 0 &&
        map->tiles[ngh_pos.first][ngh_pos.second] != -1 &&
        !GameController::Get()->PlayerHere(ngh_pos))
    {

      Content neighbor(ngh_pos, actual.weight + 1,
                       actual.weight + 1 + dist(ngh_pos, end), act_pos);

      if (!(closedList.find(neighbor) || openList.find(neighbor)))
      {
        openList.push(neighbor);
        if (dist(end, neighbor.position) + neighbor.weight < closest.prediction)
          closest = {neighbor.position, neighbor.weight,
                     dist(end, neighbor.position) + neighbor.weight,
                     neighbor.parent};
      }
    }
  };

  /*std::cout << "Start "
            << "[" << start.first << ":" << start.second << "] "
            << "End "
            << "[" << end.first << ":" << end.second << "] " << std::endl;*/

  bool find = false;

  while (!openList.empty() && !find)
  {
    Content actual = openList.top();
    openList.pop();

    /*std::cout << "NEW TILE "
              << "[" << actual.position.first << ":" << actual.position.second
              << "] " << std::endl;*/

    if (actual.position == end)
    {
      // std::cout << "END ATTEINT " << std::endl;
      std::pair<int, int> parent = actual.parent;
      while (parent != start)
      {
        do
        {
          actual = closedList.top();
          closedList.pop();
        } while (actual.position != parent);
        parent = actual.parent;
      }
      return actual.position;
    }
    else
    {

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

  if (closest.parent.first == -1)
    return start;

  // std::cout << "END PAR BLOCAGE ATTEINT " << std::endl;
  std::pair<int, int> parent = closest.parent;
  while (parent != start)
  {
    do
    {
      /*  std::cout << "parent: [" << parent.first << ":" << parent.second
                << "] closest: [" << closest.position.first << ":"
                << closest.position.second << "]" << std::endl;*/
      closest = closedList.top();
      closedList.pop();
    } while (closest.position != parent);
    parent = closest.parent;
  }
  return closest.position;
}

void GameController::loseSun(Player *player)
{

  if (player->getSunshine() > 0)
  {

    player->setSunshine(player->getSunshine() - 1);
    std::pair<int, int> posSun = findFreeTile(player);
    int s = 0;
    bool found = false;

    // find first sun in -1,-1
    while (!found)
    {
      if ((suns[s]->getX() == -1 && suns[s]->getY() == -1) || s == nbrSun)
      {
        found = true;
      }
      else
      {
        s++;
      }
    }

    if (s == nbrSun)
    {
      std::cerr << "No more sun available" << std::endl;
      exit(1);
    }
    else
    {
      suns[s]->setX(posSun.first);
      suns[s]->setY(posSun.second);
      map->tiles[posSun.first][posSun.second] = 1000 + s;
    }
  }
}

std::pair<int, int> GameController::findFreeTile(Player *player)
{

  std::pair<int, int> pos = player->getLocation();
  std::pair<int, int> posSun = pos;

  for (int i = pos.first - 2; i < pos.first + 2; i++)
  {
    for (int j = pos.second - 2; j < pos.second + 2; j++)
    {
      if (EvaluateTile(i, j) == 0 && i != pos.first && j != pos.second)
      {
        posSun.first = i;
        posSun.second = j;
      }
    }
  }

  return posSun;
}

bool GameController::PlayerHere(std::pair<int, int> loc)
{
  for (int p = 1; p <= nbrPlayer; p++)
  {
    if (players[p]->getLocation() == loc)
      return true;
  }

  return false;
}

void GameController::PlaceNewObject(IPlaceable *o)
{
  int index = 0;
  for (int i = 1; i < 80; i++)
  {
    if (objects[i] == nullptr)
    {
      index = i;
      break;
    }
  }
  objects[index] = o;
  map->SetAtIndex(o->getY(), o->getX(), 10 + index);
}
