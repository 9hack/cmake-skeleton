#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "aldente.hpp"

void aldente() {
  namespace asio = boost::asio;

  asio::io_service io;
  asio::deadline_timer t(io, boost::posix_time::seconds(1));
  t.wait();
  std::cout << HELLO_WORLD << std::endl;
}
