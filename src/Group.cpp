/**
 *
 * \file Group.cpp
 * \brief Source file for our Group class
 * \author XIE Ao
 * \date 02/01/2023
 *
 * For method description, see the header
 *
 **/

#include "../includes/Group.hpp"

/*****************************************************************************/
/*                                                                           */
/*                               Constructor                                 */
/*                                                                           */
/*****************************************************************************/

Group::Group() {}
Group::Group(int id) : Group(id, "default") {}

// With overwrite, we can create a team with his name.
Group::Group(int id, std::string name) {
  this->_id = id;
  this->_name = name;
  this->_num_player = 0;
}

/*****************************************************************************/
/*                                                                           */
/*                                Destructor                                 */
/*                                                                           */
/*****************************************************************************/

Group::~Group() {
  // Player delete individually
}

void Group::AddPlayer(Player *p) {
  players[_num_player] = p;
  _num_player++;
}

bool Group::SameGroup(const Group *g) const { return g == this; }

bool Group::OnMyGroup(const Player *p) const {
  return p != nullptr && p->getGroup() == this;
}
