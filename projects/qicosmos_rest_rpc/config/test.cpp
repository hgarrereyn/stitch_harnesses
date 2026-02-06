#include <iostream>
#include <string>
#include <rest_rpc/error_code.h>
#include <rest_rpc/logger.hpp>
#include <rest_rpc/md5.hpp>
#include <rest_rpc/function_name.h>

using namespace rest_rpc;

int add(int a, int b) { return a + b; }

int main() {
  // Test error code category and message
  std::error_code ec = make_error_code(rpc_errc::ok);
  if (ec.message() != std::string("ok")) {
    std::cerr << "unexpected message: " << ec.message() << std::endl;
    return 1;
  }

  // Test logger (should not crash)
  REST_LOG_INFO << "rest_rpc test starting";

  // Test MD5 hash utility
  const char* data = "hello world";
  uint32_t h = MD5::MD5Hash32(data, (uint32_t)std::char_traits<char>::length(data));
  // Simple sanity: hash should be non-zero for typical strings
  if (h == 0) {
    std::cerr << "hash was zero" << std::endl;
    return 1;
  }

  // Test function name extraction utility
  constexpr auto name = rest_rpc::get_func_name<add>();
  if (name.empty()) {
    std::cerr << "function name empty" << std::endl;
    return 1;
  }

  REST_LOG_INFO << "All checks passed. Hash: " << h << ", func: " << std::string(name);
  return 0;
}
