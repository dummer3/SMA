#include "Group.hpp"

Group::Group(){}
Group::Group(int id) : Group(id, "default") {}

// With overwrite, we can create a team with his name.
Group::Group(int id, std::string name) {
  this->_id = id;
  this->_name = name;
  this->_num_player = 0;
}

void Group::AddPlayer(Player *p) {
  players[_num_player] = p;
  std::cout << "groupe " << _id << ":" << _num_player << std::endl;
  _num_player++;
}

bool Group::SameGroup(const Group *g) const { return g == this; }

bool Group::OnMyGroup(const Player *p) const {
  return p != nullptr && p->getGroup() == this;
}
