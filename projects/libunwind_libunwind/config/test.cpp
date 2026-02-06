#include <stdio.h>
#include <libunwind.h>

int foo(int n);

int foo(int n) {
    if (n <= 0) return 0;
    return foo(n-1) + n;
}

int main() {
    // Simple recursion to have a few frames
    volatile int x = foo(3);
    (void)x;

    unw_context_t uc;
    if (unw_getcontext(&uc) != 0) {
        printf("unw_getcontext failed\n");
        return 0;
    }

    unw_cursor_t cur;
    if (unw_init_local(&cur, &uc) != 0) {
        printf("unw_init_local failed\n");
        return 0;
    }

    int frames = 0;
    while (unw_step(&cur) > 0 && frames < 32) {
        unw_word_t ip = 0;
        if (unw_get_reg(&cur, UNW_REG_IP, &ip) == 0) {
            // Just print a few instruction pointers
            if (frames < 5) {
                printf("frame %d: ip=0x%lx\n", frames, (unsigned long)ip);
            }
        }
        frames++;
    }
    printf("total frames walked: %d\n", frames);
    return 0;
}
