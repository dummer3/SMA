#include <iostream>
#include <cstring>
#include "Map.hpp"


Map::Map(int width, int height): width(width), height(height)
{
    memset(tiles,0,sizeof(int)*width*height);
}

Map::Map(int width, int height, int tiles[MAX_HEIGHT][MAX_WIDTH] ): Map(width,height)
{

}

Map::Map(): Map(12,24) 
{}


void Map::GenerateMap()
{
    
    memset(tiles,0,sizeof(int)*width*height);
    for(int i = 1; i < height-1; i++)
    {
        for (int j = 1; j < width-1; j++)
        {
            float proba = 0.2;
            for(int x = -1; x <= 1; x++)
            {
                for(int y = -1; y <= 1; y++)
                {
                    if(tiles[i+y][j+x] == -1)
                    
                    proba+=0.1;
                    
                }
            }
            if(rand() < proba*RAND_MAX)
            {
                tiles[i][j] = -1;
            }
            
        }
    }
}

void Map::PrintMap()
{
    for(int i = 0; i < height; i++ )
    {
        
        for(int j = 0; j < width; j++)
        {
            std::cout << "|" << tiles[i][j]; 
        }
        std::cout << "|" << std::endl;
    }
}

