#include <stdio.h>
extern "C" {
#include "yarn.h"
#include "try.h"
}

static void worker(void *arg) {
    lock *lk = (lock *)arg;
    possess(lk);
    twist(lk, TO, 1);
}

int main() {
    ball_t err;
    int caught = 0;
    try {
        throw(42, "hello %s %d", "world", 7);
    }
    catch(err) {
        if (err.code == 42 && err.why != NULL) {
            caught = 1;
        }
        drop(err);
    }

    lock *lk = new_lock(0);
    thread *th = launch(worker, lk);

    possess(lk);
    wait_for(lk, TO_BE, 1);
    release(lk);

    join(th);
    free_lock(lk);

    printf("caught=%d\n", caught);
    return caught ? 0 : 1;
}
