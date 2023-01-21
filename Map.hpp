#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "Map.hpp"
#include <stdio.h>
#include <cstdlib>

const int MAX_WIDTH = 100;
const int MAX_HEIGHT = 100;

class Map
{
    private:
    int height;
    int width;

    int tiles[MAX_HEIGHT][MAX_WIDTH]; 

    public:
    Map(int,int,int[MAX_HEIGHT][MAX_WIDTH]);
    Map(int,int);
    Map();

    void GenerateMap();
    void PrintMap();
};


#endif
