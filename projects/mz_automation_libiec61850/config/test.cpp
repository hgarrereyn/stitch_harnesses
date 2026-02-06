#include <stdio.h>
#include <string.h>
extern "C" {
#include "linked_list.h"
}

int main() {
    LinkedList list = LinkedList_create();
    const char* hello = "hello";
    const char* world = "world";
    LinkedList_add(list, (void*)hello);
    LinkedList_add(list, (void*)world);

    int size = LinkedList_size(list);
    printf("List size: %d\n", size);

    // Iterate and print
    for (LinkedList el = list; el != NULL; el = LinkedList_getNext(el)) {
        const char* s = (const char*)LinkedList_getData(el);
        if (s)
            printf("Item: %s\n", s);
    }

    // cleanup without freeing the string literals
    LinkedList_destroyStatic(list);
    return 0;
}
