#include <deque>
#include <queue>

template <class Type, class Container = std::deque<Type>>
class f_queue : public std::queue<Type, Container> {
public:
  bool find(const Type &val) const {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      if (*first == val)
        return true;
      ++first;
    }
    return false;
  }
};
