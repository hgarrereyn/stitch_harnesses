#include <iostream>
#include <elements/support/color.hpp>
#include <elements/element/label.hpp>

int main() {
    using namespace cycfi::elements;
    color c = colors::red.opacity(0.5);
    auto lbl = share(label("Hello Elements"));
    bool before = lbl->is_enabled();
    lbl->enable(false);
    bool after = lbl->is_enabled();
    std::cout << "Color: (" << c.red << "," << c.green << "," << c.blue << ")" << std::endl;
    std::cout << "Enabled before: " << before << ", after: " << after << std::endl;
    return 0;
}
