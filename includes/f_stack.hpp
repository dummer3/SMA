#include <deque>
#include <stack>

template <class Type, class Container = std::deque<Type>>
class f_stack : public std::stack<Type, Container> {
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
