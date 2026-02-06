#include <rtthread.h>
#include <stdio.h>
int main(){
    rt_tick_t t = rt_tick_from_millisecond(1234);
    printf("ticks=%u\n", (unsigned)t);
    return 0;
}
