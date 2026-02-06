#include <sqlite3/sqlite3.h>
#include <cstdio>
#include <cstring>

int main(){
    sqlite3 *db=nullptr; char *errmsg=nullptr; int rc=0;
    rc = sqlite3_open(":memory:", &db);
    if(rc!=SQLITE_OK){
        printf("open failed: %d\n", rc); return 0;
    }
    const char *sql = "CREATE TABLE t(x INT); INSERT INTO t VALUES(1);";
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);
    if(rc!=SQLITE_OK){
        printf("exec failed: %d %s\n", rc, errmsg?errmsg:"\n");
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 0;
    }
    int count = 0;
    auto cb = [](void* data, int argc, char **argv, char **col)->int{
        int *cnt = (int*)data; (*cnt)++; return 0; };
    rc = sqlite3_exec(db, "SELECT * FROM t;", cb, &count, &errmsg);
    if(rc==SQLITE_OK) printf("rows=%d\n", count);
    else printf("query failed: %d %s\n", rc, errmsg?errmsg:"\n");
    sqlite3_free(errmsg);
    sqlite3_close(db);
    return 0;
}
