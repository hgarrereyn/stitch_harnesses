#include <iostream>
#include <string>
#include <httplib.h>

int main() {
  // Use a few header-only utilities without performing real network I/O
  std::string url = "https://example.com/search?q=hello world";
  std::string encoded = httplib::encode_uri(url);
  std::string decoded = httplib::decode_uri(encoded);

  // Construct client and server objects without using them, to ensure types are available
  httplib::Client cli("http://localhost", 8080);
  httplib::Server svr;

  // Basic sanity to use a small part of the API
  std::cout << (decoded.find("hello") != std::string::npos ? "ok" : "fail") << std::endl;
  std::cout << httplib::to_string(httplib::Error::Success) << std::endl;
  return 0;
}
