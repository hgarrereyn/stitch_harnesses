#include <cstdio>
#include <missioncontrol_shim.h>
int main(){
    const unsigned char data[5] = {1,2,3,4,5};
    int s = mc_sum_bytes(data, 5);
    std::printf("sum=%d\n", s);
    return s==15 ? 0 : 1;
}
