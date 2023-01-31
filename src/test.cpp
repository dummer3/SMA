#include<iostream>
#include "Map.hpp"

int main(int, char **) {

  srand(time(0));

  Map m(36, 24, 1, 3);

  m.GenerateAllMap();
  m.PrintMap();
  m.GenerateHalfMap();
  m.PrintMap();
  m.GenerateQuarterMap();
  m.PrintMap();
  m.GenerateQuarterMap();
  m.PrintMap();
  return 0;
}
