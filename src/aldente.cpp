#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "aldente.hpp"

void aldente() {
  namespace asio = boost::asio;
  namespace pst = boost::posix_time;
  namespace bsys = boost::system;

  asio::io_service io;
  asio::deadline_timer t(io, pst::seconds(1));

  int count = 0;
  std::function<void (const bsys::error_code)> counter =
    [&](const bsys::error_code &) {
      if (count < 5) {
        ++count;
        std::cout << "Counted " << count << " times." << std::endl;
        t.expires_at(t.expires_at() + pst::seconds(1));
        t.async_wait(counter);
      }
    };
  t.async_wait(counter);

  io.run();
  std::cout << "Final count: " << count << "." << std::endl;
}
