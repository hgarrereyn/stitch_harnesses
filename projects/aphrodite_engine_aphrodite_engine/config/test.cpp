#include <iostream>
#include <cstdlib>
#include <aphrodite_kernels/core/math.hpp>
#include <aphrodite_kernels/core/batch_invariant.hpp>
#include <aphrodite_kernels/core/exception.hpp>

int main() {
    // Test math utilities
    uint32_t vals[] = {0,1,2,3,4,5,7,8,9,31,32,33};
    for (uint32_t v : vals) {
        uint32_t np2 = next_pow_2(v);
        (void)np2;
    }
    int a = 10, b = 3;
    auto q = div_ceil(a,b);
    auto r1 = round_to_previous_multiple_of(17, 8);
    auto r2 = round_to_next_multiple_of(17, 8);

    // Test batch_invariant env flag
    unsetenv("APHRODITE_BATCH_INVARIANT");
    bool def_false = aphrodite::aphrodite_is_batch_invariant();

    setenv("APHRODITE_BATCH_INVARIANT", "1", 1);
    bool def_true = aphrodite::aphrodite_is_batch_invariant();

    // Use macro to ensure header compiled
    if (!APHRODITE_IMPLIES(def_true, def_true)) {
        std::cerr << "Macro failed" << std::endl;
        return 1;
    }

    std::cout << "q=" << q << ", r1=" << r1 << ", r2=" << r2
              << ", def_false=" << def_false
              << ", def_true=" << def_true << std::endl;
    return 0;
}
