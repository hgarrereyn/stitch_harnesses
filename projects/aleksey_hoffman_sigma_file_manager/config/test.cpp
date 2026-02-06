#include <cstdio>
#include <cstring>
extern "C" {
#include "sigma.h"
}
int main(){
  const char* v = sigma_version();
  if(!v || std::strlen(v)==0) return 1;
  int s = sigma_add(2, 3);
  std::printf("Sigma stub version: %s; 2+3=%d\n", v, s);
  return 0;
}
