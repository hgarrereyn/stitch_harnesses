#include <cstdio>
#include <sof/list.h>

struct Node {
    int value;
    list_item item; // from sof/list.h
};

int main() {
    list_item head = LIST_INIT(head);
    Node a{1};
    Node b{2};

    list_item_append(&a.item, &head);
    list_item_append(&b.item, &head);

    // Count elements
    int count = 0;
    for (list_item *it = head.next; it != &head; it = it->next) {
        ++count;
    }

    std::printf("SOF list count: %d\n", count);
    return 0;
}
