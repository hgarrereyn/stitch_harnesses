extern "C" {
#include <tmux_public.h>
}
#include <stdio.h>

int main() {
    int s = tmux_public_sum(20, 22);
    printf("sum=%d\n", s);
    return 0;
}
