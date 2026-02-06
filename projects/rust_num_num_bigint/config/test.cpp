#include <cstdio>
#include <num_bigint.h>
int main(){
    int v = num_bigint_version();
    std::printf("num-bigint shim version: %d\n", v);
    return 0;
}
