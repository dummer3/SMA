#include "Group.hpp"

Group::Group(){}
Group::Group(int id){
    this->_id = id;
    this-> _name = "default";
    this-> _num_player = NUM_PLAYER;
}

// With overwrite, we can create a team with his name.
Group::Group(int id, std::string name){
    this->_id = id;
    this->_name = name;
    this->_num_player = NUM_PLAYER;
}