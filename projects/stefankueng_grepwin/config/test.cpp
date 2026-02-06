#include <stdio.h>
#include <string.h>
#include "grepwin_dummy.h"
int main(){
  const char* v = grepwin_version();
  int s = grepwin_add(7, 35);
  if(!v || strcmp(v, "grepWin-shim 0.1")!=0) {
    printf("Unexpected version: %s\n", v?v:"(null)");
    return 1;
  }
  printf("%s sum=%d\n", v, s);
  return s==42?0:1;
}
