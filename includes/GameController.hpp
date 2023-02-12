#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Map.hpp"
#include "Player.hpp"
#include "Sun.hpp"

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

  Group *g1;
  Group *g2;

  GameController(int nbrPlayer, int height, int width);

public:
  GameController(const GameController &) = delete;
  void operator=(const GameController &) = delete;
  void CreateGame();
  void InitGame();
  void NewRound();
  void ManagePlayer();
  int EvaluateTile(int, int);

  static GameController *Get(int = 8);

  void Destroy();

  // Never use it, infinit loop !!!
  //~GameController();
};

#endif /* GAMECONTROLLER_H */
