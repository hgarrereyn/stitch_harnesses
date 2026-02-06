#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "http_pattern_matcher/path_matcher.h"

int main() {
  using namespace google::http::pattern_matcher;

  // Build a simple matcher mapping GET /v1/shelves/*/books/* to a method name.
  PathMatcherBuilder<std::string> builder;
  bool ok = builder.Register("GET", "/v1/shelves/*/books/*", "", std::string("get_book"));
  if (!ok) {
    std::cout << "Register failed\n";
    return 0;
  }
  auto matcher = builder.Build();

  // Try a matching path.
  std::string method = matcher->Lookup("GET", "/v1/shelves/123/books/abc");
  std::cout << "Lookup result: " << method << "\n";

  // Test URL unescape helper.
  std::string escaped = "%2Ffoo%20bar";
  std::string unescaped = UrlUnescapeString(escaped, UrlUnescapeSpec::kAllCharacters);
  std::cout << "Unescaped: " << unescaped << "\n";

  return 0;
}
