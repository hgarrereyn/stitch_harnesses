#include <iostream>
#include <string>
#include "flex/utils/result.h"

int main() {
    // Basic Status usage
    gs::Status ok = gs::Status::OK();
    std::cout << "Status: " << ok.ToString() << "\n";

    // Create a successful Result<int>
    gs::Result<int> r(42);
    if (r.ok()) {
        std::cout << "Result holds: " << r.value() << "\n";
    }

    // Create an error Status and wrap into Result<std::string>
    gs::Status err(static_cast<gs::StatusCode>(gs::flex::interactive::Code::INVALID_ARGUMENT),
                   std::string("invalid input"));
    gs::Result<std::string> r2(err);
    std::cout << "Error? " << (!r2.ok() ? "yes" : "no") << "\n";

    return 0;
}
