#ifndef _Group
#define _Group

const int NUM_PLAYER = 4;

#include <iostream>
#include <string>

class Group{
    private:
    int _id;
    std::string _name;
    int _num_player;

    public:
    Group();
    Group(int id);
    Group(int id, std::string name);
};

#endif