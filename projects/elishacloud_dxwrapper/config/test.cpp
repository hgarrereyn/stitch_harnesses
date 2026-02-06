#include <cstdio>
#include <dxwrapper.h>
int main(){
    int v = dxw_hello();
    std::printf("dxwrapper shim says %d\n", v);
    return v == 42 ? 0 : 1;
}
