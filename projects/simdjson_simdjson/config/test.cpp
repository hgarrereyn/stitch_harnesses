#include <iostream>
#include "simdjson.h"

int main() {
  try {
    simdjson::dom::parser parser;
    // Valid JSON using a raw string literal with padding
    simdjson::dom::element doc = parser.parse(R"({"message":"hello","value":42})"_padded);
    std::string_view msg;
    int64_t val = 0;
    auto err1 = doc["message"].get(msg);
    auto err2 = doc["value"].get(val);
    if (err1) { std::cerr << "error reading message: " << err1 << "\n"; return 1; }
    if (err2) { std::cerr << "error reading value: " << err2 << "\n"; return 1; }
    std::cout << "Message: " << msg << ", Value: " << val << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
