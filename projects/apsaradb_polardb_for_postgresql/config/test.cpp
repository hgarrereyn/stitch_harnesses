#include <iostream>
#include <libpq-fe.h>

int main() {
    int v = PQlibVersion();
    std::cout << "libpq version: " << v << std::endl;
    // Create and clear a simple PGresult to touch a bit more API
    PGresult* res = PQmakeEmptyPGresult(nullptr, PGRES_EMPTY_QUERY);
    if (res) {
        std::cout << "Status: " << PQresStatus(PQresultStatus(res)) << std::endl;
        PQclear(res);
    }
    return 0;
}
