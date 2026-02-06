#include <stdio.h>
#include <stdlib.h>
#include <sudo_queue.h>

struct node {
    int v;
    TAILQ_ENTRY(node) entries;
};

TAILQ_HEAD(node_list, node);

int main() {
    node_list head;
    TAILQ_INIT(&head);

    // Push a few nodes
    for (int i = 0; i < 3; i++) {
        node *n = (node*)malloc(sizeof(*n));
        n->v = i + 1;
        TAILQ_INSERT_TAIL(&head, n, entries);
    }

    // Iterate and sum
    int sum = 0;
    node *it;
    TAILQ_FOREACH(it, &head, entries) {
        sum += it->v;
    }

    // Pop and free
    while (!TAILQ_EMPTY(&head)) {
        node *n = TAILQ_FIRST(&head);
        TAILQ_REMOVE(&head, n, entries);
        free(n);
    }

    printf("sum=%d\n", sum);
    return 0;
}
