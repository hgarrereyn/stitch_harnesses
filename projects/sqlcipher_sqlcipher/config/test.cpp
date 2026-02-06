#include <sqlite3.h>
#include <stdio.h>

int main(){
    sqlite3 *db = NULL;
    if(sqlite3_open(":memory:", &db) != SQLITE_OK){
        fprintf(stderr, "open failed: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    const char *sql = "CREATE TABLE t(x); INSERT INTO t VALUES (42);";
    char *errmsg = NULL;
    if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK){
        fprintf(stderr, "exec failed: %s\n", errmsg ? errmsg : "unknown");
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_stmt *st = NULL;
    if(sqlite3_prepare_v2(db, "SELECT x FROM t", -1, &st, NULL) != SQLITE_OK){
        fprintf(stderr, "prepare failed: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    int rc = sqlite3_step(st);
    if(rc == SQLITE_ROW){
        int v = sqlite3_column_int(st, 0);
        printf("value=%d\n", v);
    } else {
        fprintf(stderr, "step rc=%d\n", rc);
    }
    sqlite3_finalize(st);
    sqlite3_close(db);
    return 0;
}
