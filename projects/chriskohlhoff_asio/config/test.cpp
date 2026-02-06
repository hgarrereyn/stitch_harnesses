#include <asio.hpp>
#include <chrono>
#include <iostream>

int main() {
  try {
    asio::io_context io;
    asio::steady_timer t(io, std::chrono::milliseconds(10));
    t.wait();
    std::cout << "asio io_context and timer work" << std::endl;
  } catch (std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
