#include <inotifytools/inotifytools.h>
#include <stdio.h>

int main() {
    if (!inotifytools_initialize()) {
        printf("initialize failed (this may still indicate library linked properly)\n");
    }
    int watches = inotifytools_get_max_user_watches();
    int inst = inotifytools_get_max_user_instances();
    int queued = inotifytools_get_max_queued_events();
    printf("limits: watches=%d instances=%d queued=%d\n", watches, inst, queued);
    inotifytools_cleanup();
    return 0;
}
