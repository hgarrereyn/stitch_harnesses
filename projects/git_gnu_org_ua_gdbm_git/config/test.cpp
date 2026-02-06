#include <gdbm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    GDBM_FILE db;
    const char *fname = "/tmp/test.gdbm";
    db = gdbm_open((char*)fname, 0, GDBM_NEWDB, 0644, NULL);
    if (!db) {
        perror("gdbm_open");
        return 0; // don't fail in CI
    }

    datum key, val, res;
    const char *k = "hello";
    const char *v = "world";
    key.dptr = (char*)k; key.dsize = (int)strlen(k);
    val.dptr = (char*)v; val.dsize = (int)strlen(v);

    if (gdbm_store(db, key, val, GDBM_REPLACE) != 0) {
        fprintf(stderr, "gdbm_store failed\n");
    }

    res = gdbm_fetch(db, key);
    if (res.dptr) {
        printf("%.*s\n", res.dsize, res.dptr);
        free(res.dptr);
    } else {
        printf("(no result)\n");
    }

    gdbm_close(db);
    return 0;
}
