#include <iostream>
#include <vector>
#include <string>
extern "C" {
#include <shl_htable.h>
}
#include <cstdlib>

int main() {
    shl_htable ht;
    shl_htable_init_str(&ht);

    std::vector<std::string> keys = {"alpha", "beta", "gamma"};
    std::vector<char**> boxes;

    // Insert needs a stable pointer-to-pointer; allocate a box for each key
    for (auto &k : keys) {
        char **box = (char**)malloc(sizeof(char*));
        *box = strdup(k.c_str());
        size_t h = 0;
        int r = shl_htable_insert_str(&ht, box, &h);
        if (r) {
            std::cerr << "insert failed for " << k << "\n";
            return 1;
        }
        boxes.push_back(box);
    }

    // Lookup by string
    for (auto &k : keys) {
        char **out = nullptr;
        size_t h = 0;
        bool found = shl_htable_lookup_str(&ht, k.c_str(), &h, &out);
        if (!found || !out || std::string(*out) != k) {
            std::cerr << "lookup failed for " << k << "\n";
            return 2;
        }
    }

    // Cleanup
    for (auto box : boxes) {
        if (box) {
            if (*box) free(*box);
            free(box);
        }
    }

    std::cout << "Hashtable test OK\n";
    return 0;
}
