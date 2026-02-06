#include <xrpl/basics/Number.h>
#include <xrpl/beast/utility/Zero.h>

int main() {
    // Use a header-only constexpr function
    bool ok = xrpl::isPowerOfTen(1000);
    if (!ok) return 1;

    // Access a simple constant from beast
    auto z = beast::zero;
    (void)z;
    return 0;
}
