#include <iostream>
#include <string>
#include "/fuzz/install/include/infinity_client/infinity_client.h"

int main() {
    using namespace infinity::client;
    ClientStatus st = ClientStatus::OK();
    std::cout << "ClientStatus OK? " << (st.IsOK() ? "yes" : "no") << "\n";

    // Exercise a few API enums/types without making network calls
    infinity::client::CreateOption opt = infinity::client::CreateOption::kIgnoreIfExists;
    (void)opt;

    // Just construct simple structs
    DatabaseInfo db;
    db.name_ = "default_db";
    db.storage_path_ = "/var/infinity";

    TableInfo tbl;
    tbl.database_name_ = db.name_;
    tbl.name_ = "t";
    tbl.row_count_ = 0;

    std::cout << "DB: " << db.name_ << ", table: " << tbl.name_ << ", rows: " << tbl.row_count_ << "\n";
    return 0;
}
