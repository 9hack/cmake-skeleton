#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "aldente.hpp"

void aldente() {
  namespace asio = boost::asio;
  namespace pst = boost::posix_time;
  namespace bsys = boost::system;

  asio::io_service io;
  asio::io_service::strand s(io);
  asio::deadline_timer t1(io, pst::seconds(1));
  asio::deadline_timer t2(io, pst::seconds(1));

  int count = 0;
  std::function<void (const bsys::error_code &)> c1 = s.wrap(
    [&](const bsys::error_code &) {
      if (count < 5) {
        ++count;
        std::cout << "c1: Counted " << count << " times." << std::endl;
        t1.expires_at(t1.expires_at() + pst::seconds(1));
        t1.async_wait(c1);
      }
    });
  std::function<void (const bsys::error_code &)> c2 = s.wrap(
    [&](const bsys::error_code &) {
      if (count < 5) {
        ++count;
        std::cout << "c2: Counted " << count << " times." << std::endl;
        t2.expires_at(t2.expires_at() + pst::seconds(1));
        t2.async_wait(c2);
      }
    });
  t1.async_wait(c1);
  t2.async_wait(c2);

  boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
  t.join();
  std::cout << "Final count: " << count << "." << std::endl;
}
