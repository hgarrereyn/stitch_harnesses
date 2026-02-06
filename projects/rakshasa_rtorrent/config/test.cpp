#include <iostream>
#include <utils/lockfile.h>

int main() {
    utils::Lockfile lf;
    lf.set_path("/tmp/rtorrent_fuzz_lockfile.lock");

    bool locked = lf.try_lock();
    std::cout << "try_lock: " << (locked ? "true" : "false") << "\n";

    std::cout << "is_locked: " << (lf.is_locked() ? "true" : "false") << "\n";
    std::cout << "locked_by: " << lf.locked_by_as_string() << "\n";

    bool ok = lf.unlock();
    std::cout << "unlock: " << (ok ? "true" : "false") << "\n";

    return 0;
}
