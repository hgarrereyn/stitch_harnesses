#include <iostream>
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

int main() {
    absl::string_view name = "Abseil";
    std::string msg = absl::StrCat("Hello, ", name, "! ", 123);
    std::cout << msg << "\n";
    return 0;
}
