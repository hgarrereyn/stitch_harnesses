#include <iostream>
#include "udf/openmldb_udf.h"

int main() {
    openmldb::base::UDFContext ctx{}; // default init
    ctx.pool = nullptr;
    ctx.ptr = nullptr;
    std::cout << "OpenMLDB UDF header loaded. Version="
              << openmldb::base::OPENMLDB_UDF_LIBRARY_VERSION << "\n";
    return 0;
}
