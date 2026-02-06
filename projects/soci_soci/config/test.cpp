#include <soci/soci.h>
#include <soci/empty/soci-empty.h>
#include <iostream>

int main() {
    try {
        soci::session sql(soci::empty, "");
        if (sql.is_connected()) {
            std::cout << "SOCI session (empty backend) is connected.\n";
        } else {
            std::cout << "SOCI session not connected.\n";
        }
        // Simple no-op query composition using sugar, without executing.
        sql.get_query_stream() << "SELECT 1" << sql.get_dummy_from_clause();
        std::string q = sql.get_query();
        std::cout << "Composed query: " << q << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
