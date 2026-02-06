#include <cstdio>
#include <tsk/libtsk.h>

int main() {
    // Print version info using the library macro and a function
    tsk_printf("TSK version: %s\n", TSK_VERSION_STR);

    // Exercise a small API: create a stack and push/pop
    TSK_STACK *st = tsk_stack_create();
    if (!st) {
        tsk_printf("Failed to create stack\n");
        return 1;
    }
    tsk_stack_push(st, 42);
    tsk_stack_push(st, 7);
    int found = tsk_stack_find(st, 42);
    tsk_printf("Found 42? %d\n", found);
    tsk_stack_pop(st);
    tsk_stack_free(st);
    return 0;
}
