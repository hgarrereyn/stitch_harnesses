#include <iostream>
#include "xbmc/utils/Base64.h"

int main(){
  const std::string input = "hello fuzzing";
  std::string enc = Base64::Encode(input);
  std::string dec = Base64::Decode(enc);
  std::cout << enc << "\n" << dec << "\n";
  return dec == input ? 0 : 1;
}
