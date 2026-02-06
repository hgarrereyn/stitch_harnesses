#include "duckdb.hpp"
#include <iostream>

int main() {
    try {
        duckdb::DuckDB db(nullptr);
        duckdb::Connection con(db);
        auto res = con.Query("CREATE TABLE t(i INTEGER);");
        if (!res || res->HasError()) return 1;
        res = con.Query("INSERT INTO t VALUES (42), (7);");
        if (!res || res->HasError()) return 1;
        auto result = con.Query("SELECT sum(i) FROM t;");
        if (!result || result->HasError()) return 1;
        auto val = result->GetValue(0, 0).GetValue<int64_t>();
        std::cout << "sum=" << val << std::endl;
        return val == 49 ? 0 : 1;
    } catch (...) {
        return 1;
    }
}
