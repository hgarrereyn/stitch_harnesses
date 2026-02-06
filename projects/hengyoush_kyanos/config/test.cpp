#include <kyanos_c.h>
#include <iostream>
int main(){
  int x = kyanos_add(2, 40);
  std::cout << "kyanos_add(2,40)=" << x << "\n";
  return x == 42 ? 0 : 1;
}
