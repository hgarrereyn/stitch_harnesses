#include <collectd/types.h>
#include <collectd/client.h>
#include <iostream>

int main() {
    lcc_identifier_t a = LCC_IDENTIFIER_INIT;
    lcc_identifier_t b = LCC_IDENTIFIER_INIT;
    // compare two identifiers (should be equal -> 0)
    int cmp = lcc_identifier_compare(&a, &b);
    std::cout << "lcc_identifier_compare: " << cmp << "\n";

    // Prepare a simple value list structure
    lcc_value_list_t vl = LCC_VALUE_LIST_INIT;
    vl.interval = 10.0;
    (void)vl; // suppress unused warning

    return 0;
}
