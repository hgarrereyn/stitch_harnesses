#include <iostream>
#include <helium/helium.h>
int main(){
    std::cout << "Hello from: " << helium_hello() << "\n";
    int s = helium_sum(7, 35);
    std::cout << "Sum: " << s << "\n";
    if(s != 42) return 1;
    return 0;
}
