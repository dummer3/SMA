#include<iostream>
#include "Map.hpp"

int main(int, char**) {

  srand(time(0));

  Map m(12,12);

  m.GenerateMap();
  m.PrintMap();
  return 0;
}