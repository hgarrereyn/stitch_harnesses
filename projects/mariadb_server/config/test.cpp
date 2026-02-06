#include <mysql.h>
#include <cstdio>

int main() {
    const char* info = mysql_get_client_info();
    if (info) {
        std::printf("MariaDB client info: %s\n", info);
    } else {
        std::printf("No client info available.\n");
    }
    MYSQL* conn = mysql_init(nullptr);
    if (!conn) {
        std::printf("mysql_init failed\n");
        return 0;
    }
    mysql_close(conn);
    return 0;
}
