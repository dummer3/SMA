#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Map.hpp"
#include "Player.hpp"
#include "Sun.hpp"
#include "f_stack.hpp"
#include "p_queue.hpp"
#include <list>

class Map;
class Player;
class Group;

class GameController {
  friend Map;

private:
  GameController();
  static GameController *game;
  static Map *map;
  int nbrPlayer = 8;
  int nbrSun = 5;
  Player **players;
  Sun **suns;
  IPlaceable **objects;

  Group *g1;
  Group *g2;

  GameController(int nbrPlayer, int height, int width);

public:
  GameController(const GameController &) = delete;
  void operator=(const GameController &) = delete;
  void CreateGame();
  void InitGame();
  void NewRound();
  void ManagePlayers();
  void ManageBoxes();
  void ManageObjects();
  int EvaluateTile(int, int);
  std::pair<int, int> A(std::pair<int, int> start, std::pair<int, int> end);
  void loseSun(Player *);
  std::pair<int, int> findFreeTile(Player *);
  bool PlayerHere(std::pair<int, int>);
  void PlaceNewObject(IPlaceable *);

  static GameController *Get(int = 8);

  void Destroy();

  // Never use it, infinit loop !!!
  //~GameController();
};

#endif /* GAMECONTROLLER_H */
