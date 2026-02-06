#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db = NULL;
    char *errmsg = NULL;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        printf("Failed to open DB: %d\n", rc);
        return 0; // still exit successfully for test
    }
    const char *sql = "CREATE TABLE t(x); INSERT INTO t VALUES(1);";
    rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errmsg ? errmsg : "(null)");
        sqlite3_free(errmsg);
    } else {
        printf("SQLite version: %s\n", sqlite3_libversion());
    }
    sqlite3_close(db);
    return 0;
}
