/**
 *   \file p_queue.hpp
 *   \brief Template for a priority queue with extension
 * \author Cliquot Théo
 * \date 28/01/2023
 */

#include <queue>

/**
 *
 * \class p_queue
 * \brief Priority queue with a find function for our A algorithm
 *
 **/

template <class T, class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class p_queue : public std::priority_queue<T, Container, Compare> {
public:
  /**
   *
   * \fn bool find(const Type &val)
   * \brief return if our val is inside the queue, if not or if the new one is
   * better, insert it
   * \param const Type & val: the val to test
   * \return bool: if the val is inside our not
   *
   **/

  typedef typename std::priority_queue<
      T, Container, Compare>::container_type::const_iterator const_iterator;
  bool find(const T &val) {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      if (*first == val) {
        if (val < *first) {
          this->c.erase(first);
          return false;
        }
        return true;
      }
      ++first;
    }
    return false;
  }
};
