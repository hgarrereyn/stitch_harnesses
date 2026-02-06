#include <iostream>
#include <string>
#include "mergerfs_api.hpp"

int main() {
    using namespace mergerfs::api;

    // Check if root is a mergerfs mount (likely false in test env)
    bool is_mfs = is_mergerfs("/");
    std::cout << "is_mergerfs(/): " << (is_mfs ? "true" : "false") << "\n";

    // Try to query API paths; these will likely return negative errno
    std::string out;
    int rv = basepath("/", out);
    std::cout << "basepath rv=" << rv << ", val='" << out << "'\n";

    rv = relpath("/", out);
    std::cout << "relpath rv=" << rv << ", val='" << out << "'\n";

    rv = fullpath("/", out);
    std::cout << "fullpath rv=" << rv << ", val='" << out << "'\n";

    std::vector<std::string> paths;
    rv = allpaths("/", paths);
    std::cout << "allpaths rv=" << rv << ", count=" << paths.size() << "\n";

    return 0;
}
