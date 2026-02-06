#include <boost/hana.hpp>
#include <string>
#include <iostream>

namespace hana = boost::hana;
using namespace hana::literals;

struct A { std::string name; };
struct B { std::string name; };

int main() {
    auto xs = hana::make_tuple(A{"alpha"}, B{"beta"});
    auto names = hana::transform(xs, [](auto const& x){ return x.name; });
    static_assert(decltype(hana::length(xs))::value == 2, "length must be 2");
    auto rev = hana::reverse(names);
    std::cout << hana::at_c<0>(rev) << "," << hana::at_c<1>(rev) << "\n";
    return 0;
}
