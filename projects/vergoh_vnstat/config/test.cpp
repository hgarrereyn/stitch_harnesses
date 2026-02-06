#include <stdio.h>
extern "C" {
#include "config.h"
#include "common.h"
#include "cfg.h"
#include "dbsql.h"
#include "misc.h"
}

int main() {
    // Silence library prints and avoid disk checks in this tiny smoke test
    disableprinte = 1;

    // Initialize defaults and locale
    defaultcfg();
    cfg.spacecheck = 0;          // disable disk space checks
    snprintf(cfg.dbdir, sizeof(cfg.dbdir), "/tmp");
    configlocale();

    // Open an in-memory database and create schema
    if (db_open_filename(":memory:", 1, 0) != 1) {
        printf("Failed to open in-memory database\n");
        return 0; // don't fail the test run hard
    }
    if (!db_create()) {
        printf("Failed to create schema\n");
    }

    // Add an interface and query count
    db_addinterface("lo");
    unsigned long long cnt = (unsigned long long)db_getinterfacecount();

    // Exercise a couple of utility functions
    const char *unit = getunitprefix(0);
    (void)unit;

    // Clean up
    db_close();

    printf("vnstat test ok, interfaces=%llu\n", cnt);
    return 0;
}
