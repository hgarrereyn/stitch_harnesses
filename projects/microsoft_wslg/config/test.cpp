#include <iostream>
#include <rdpapplist/rdpapplist_server.h>

int main() {
    // We do not create a real FreeRDP context here; just ensure we can include and link.
    // Call a trivial API with a null pointer to verify linkage.
    rdpapplist_server_context_free(nullptr);
    std::cout << "rdpapplist headers available and library linked" << std::endl;
    return 0;
}
