#include <iostream>
#include <list>
#include "aldente.hpp"

using namespace std;

template <class...Args>
class EventManager {
  typedef void (*cb_t)(Args...);

  public:
    void listen(cb_t cb) {
      callbacks.push_back(cb);
    }

    void unlisten(cb_t cb) {
      callbacks.remove(cb);
    }

    void dispatch(Args... data) const {
      for (cb_t cb : callbacks)
        (*cb)(data...);
    }

  private:
    list<cb_t> callbacks;
};

void many_args(int x, int y) {
  cout << "many_args: " << x << ", " << y << endl;
}

void to_listen(string x) {
  cout << "to_listen: " << x << endl;
}

void to_unlisten(string x) {
  cout << "to_unlisten: " << x << endl;
}

int main() {
  auto string_event = EventManager<string>();

  string_event.listen(&to_listen);
  string_event.listen(&to_unlisten);

  string_event.dispatch(HELLO_WORLD);
  string_event.unlisten(&to_unlisten);
  string_event.dispatch("to_unlisten should be dead");

  auto many_event = EventManager<int, int>();

  many_event.listen(&many_args);
  many_event.dispatch(1, 2);
  many_event.unlisten(&many_args);
  many_event.dispatch(3, 4);

  return 0;
}
