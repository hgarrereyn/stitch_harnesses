#include <iostream>
#include "PaperSize.hh"

int main() {
    auto s_cm = PaperSize::getSize(PaperSize::cm, "A4", false);
    auto s_in = PaperSize::getSize(PaperSize::inch, "Letter", false);
    std::cout << "A4 (cm): " << s_cm.width << " x " << s_cm.height << "\n";
    std::cout << "Letter (in): " << s_in.width << " x " << s_in.height << "\n";
    return 0;
}
