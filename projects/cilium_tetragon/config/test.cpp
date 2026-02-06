#include <stdio.h>
#include <tetragon_dummy.h>

int main() {
    int a = 7, b = 35;
    int c = tetragon_add(a, b);
    printf("tetragon_add(%d,%d)=%d\n", a, b, c);
    return c == (a + b) ? 0 : 1;
}
