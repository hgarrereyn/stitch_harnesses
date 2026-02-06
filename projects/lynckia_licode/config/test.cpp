#include <iostream>
#include <string>
#include <erizo/lib/Base64.h>

int main() {
  std::string input = "hello fuzz";
  std::string encoded;
  std::string decoded;

  bool ok_enc = erizo::Base64::Encode(input, &encoded);
  bool ok_dec = erizo::Base64::Decode(encoded, &decoded);

  std::cout << "Encoded: " << encoded << "\n";
  std::cout << "Decoded: " << decoded << "\n";
  std::cout << (ok_enc && ok_dec && decoded == input ? "OK" : "FAIL") << "\n";
  return ok_enc && ok_dec && decoded == input ? 0 : 1;
}
