#include <queue>
template <class T, class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class p_queue : public std::priority_queue<T, Container, Compare> {
public:
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
