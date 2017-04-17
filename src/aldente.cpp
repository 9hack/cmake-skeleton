#include <iostream>
#include <list>
#include "aldente.hpp"

using namespace std;

template <class T>
class Event {
  typedef void (*cb_t)(T);

  public:
    void subscribe(cb_t cb) {
      callbacks.push_back(cb);
    }

    void unsubscribe(cb_t cb) {
      callbacks.remove(cb);
    }

    void dispatch(T data) {
      for (cb_t cb : callbacks)
        (*cb)(data);
    }

  private:
    list<cb_t> callbacks;
};

struct PositionData {
  int x;
  int y;
};
auto PositionChangeEvent = Event<PositionData>();

void do_print(PositionData p) {
  cout << "(" << p.x << ", " << p.y << ")" << endl;
}

int main() {
  PositionChangeEvent.subscribe(&do_print);
  PositionChangeEvent.dispatch({
    .y = 2,
  });
  return 0;
}
