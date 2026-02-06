#include <iostream>
#include <string>
#include <vector>

#include <spotify/json.hpp>

using namespace spotify::json;

struct Simple {
  int x = 0;
  std::string name;
};

namespace spotify { namespace json {
  template<> struct default_codec_t<Simple> {
    static codec::object_t<Simple> codec() {
      auto c = codec::object<Simple>();
      c.required("x", &Simple::x);
      c.optional("name", &Simple::name);
      return c;
    }
  };
}} // namespace spotify::json

int main() {
  try {
    // Decode a simple JSON object
    Simple s = decode<Simple>("{\"x\": 42, \"name\": \"hello\"}");
    // Encode it back
    std::string out = encode(s);
    // Also exercise basic number encode/decode
    int n = decode<int>("123");
    std::string nstr = encode(n);

    std::cout << "Decoded x=" << s.x << ", name=" << s.name << "\\n";
    std::cout << "Re-encoded: " << out << "\\n";
    std::cout << "Number roundtrip: " << n << " -> " << nstr << "\\n";
  } catch (const decode_exception &e) {
    std::cout << "Decode error: " << e.what() << "\\n";
  }
  return 0;
}
