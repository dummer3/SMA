#include "../includes/Sun.hpp"
#include "../includes/Player.hpp"

Sun::Sun(int y, int x) : IPlaceable(y, x) {}

void Sun::hitEffect(Player* player) {
  player->setSunshine(player->getSunshine() + 1);
}

Sun::~Sun() {}
