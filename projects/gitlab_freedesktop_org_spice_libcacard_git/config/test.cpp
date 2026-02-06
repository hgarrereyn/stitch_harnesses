#include <cacard/libcacard.h>
#include <stdio.h>

int main() {
    // Initialize reader subsystem and list current readers (likely none)
    vreader_init();
    VReaderList *list = vreader_get_reader_list();
    int count = 0;
    if (list) {
        VReaderListEntry *e = vreader_list_get_first(list);
        while (e) {
            VReader *r = vreader_list_get_reader(e);
            const char *name = r ? vreader_get_name(r) : "";
            if (name) {
                // just touch the name to avoid unused warnings
                putchar('\n');
            }
            e = vreader_list_get_next(e);
            count++;
        }
        vreader_list_delete(list);
    }
    printf("Readers listed: %d\n", count);
    return 0;
}
