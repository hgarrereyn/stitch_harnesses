#include <stdio.h>
extern "C" {
#include <util.h>
#include <text.h>
}

int main() {
    Text *txt = text_load(NULL); // empty buffer
    if (!txt) {
        printf("text_load failed\n");
        return 0;
    }
    const char *msg = "Hello vis lib";
    // insert at start
    text_insert(txt, 0, msg, strlen(msg));
    size_t sz = text_size(txt);
    printf("size=%zu\n", sz);
    text_free(txt);
    return 0;
}
