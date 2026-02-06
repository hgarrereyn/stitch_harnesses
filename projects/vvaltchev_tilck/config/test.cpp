#include <tilck/common/cpputils.hpp>
#include <cstdio>

int main() {
    // Use a few templates and typedefs from the header-only utilities
    using S = signed_by_size<2>::type;   // s16
    using U = unsigned_type<S>::type;    // u16
    U maxv = limits<U>::max();
    if (maxv == 0) return 1;
    std::printf("max(u16)=%u\n", (unsigned)maxv);
    return 0;
}
