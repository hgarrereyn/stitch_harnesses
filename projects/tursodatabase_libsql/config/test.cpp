#include <sqlite3.h>
int main(){
    sqlite3* db = nullptr; if(sqlite3_open(":memory:", &db)!=SQLITE_OK) return 1;
    char* err=nullptr; if(sqlite3_exec(db, "CREATE TABLE t(x); INSERT INTO t VALUES(7);", nullptr, nullptr, &err)!=SQLITE_OK){ if(err) sqlite3_free(err); sqlite3_close(db); return 2; }
    int rows=0; auto cb=[](void* p,int argc,char** argv,char** col)->int{ int* r=(int*)p; (*r)++; return 0; };
    if(sqlite3_exec(db, "SELECT x FROM t;", cb, &rows, &err)!=SQLITE_OK){ if(err) sqlite3_free(err); sqlite3_close(db); return 3; }
    sqlite3_close(db); return rows==1?0:4;
}
