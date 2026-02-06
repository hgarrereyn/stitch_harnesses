#include <iostream>
#include "jwt_verify_lib/jwt.h"
#include "jwt_verify_lib/status.h"

int main() {
  using namespace google::jwt_verify;
  Jwt jwt;
  // header: {"alg":"HS256"}, payload: {}
  std::string token = "eyJhbGciOiJIUzI1NiJ9.e30.AA";
  Status s = jwt.parseFromString(token);
  std::cout << "parse status: " << getStatusString(s) << "\n";
  if (s == Status::Ok) {
    std::cout << "alg=" << jwt.alg_ << ", kid=" << jwt.kid_ << "\n";
  }
  return 0;
}
