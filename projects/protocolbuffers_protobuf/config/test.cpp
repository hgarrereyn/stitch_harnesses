#include <upb/mem/arena.h>
#include <stdio.h>

int main() {
    upb_Arena* arena = upb_Arena_New();
    if (!arena) {
        return 1;
    }
    // Allocate a small block from the arena and write something.
    char* buf = (char*)upb_Arena_Malloc(arena, 8);
    if (!buf) {
        upb_Arena_Free(arena);
        return 1;
    }
    for (int i = 0; i < 7; ++i) buf[i] = 'A' + i;
    buf[7] = '\0';
    printf("%s\n", buf);
    upb_Arena_Free(arena);
    return 0;
}
