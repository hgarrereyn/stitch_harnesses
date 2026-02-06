#include "ih264_typedefs.h"
#include <stdio.h>
#include <stdint.h>
#include "ih264d.h"

int main() {
    void *p1 = (void*)(&ih264d_api_function);
    printf("ih264d_api_function=%p\n", p1);
    return 0;
}
