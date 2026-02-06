#include <cstdio>
#include <wds_sample.h>
int main(){
    const char* msg = wds_hello();
    unsigned char buf[5] = {1,2,3,4,5};
    int sum = wds_echo_sum(buf, 5);
    std::printf("%s: sum=%d\n", msg, sum);
    return sum == 15 ? 0 : 1;
}
