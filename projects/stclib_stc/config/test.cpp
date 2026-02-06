#include <stdio.h>
#include <stc/common.h>

#define i_type IntVec
#define i_key int
#define i_use_cmp
#include <stc/vec.h>

int main(void) {
    IntVec v = {0};
    for (int i = 3; i >= 1; --i) IntVec_push(&v, i);
    IntVec_sort(&v);
    for (c_each(i, IntVec, v)) {
        printf("%d ", *i.ref);
    }
    printf("\n");
    IntVec_drop(&v);
    return 0;
}
