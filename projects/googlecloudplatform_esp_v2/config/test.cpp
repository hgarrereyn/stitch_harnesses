#include <iostream>
#include <vector>
#include <string>
#include "src/api_proxy/path_matcher/path_matcher.h"

using espv2::api_proxy::path_matcher::PathMatcher;
using espv2::api_proxy::path_matcher::PathMatcherBuilder;
using espv2::api_proxy::path_matcher::VariableBinding;

int main() {
    using Method = void*; // simple pointer as method identifier

    PathMatcherBuilder<Method> builder;

    // Register a couple of routes
    Method m_get_books = reinterpret_cast<Method>(0x1);
    Method m_post_shelf = reinterpret_cast<Method>(0x2);

    bool ok1 = builder.Register("GET", "/v1/books/{name=**}", "", m_get_books);
    bool ok2 = builder.Register("POST", "/v1/shelves/{shelf}/books", "body", m_post_shelf);

    if (!ok1 || !ok2) {
        std::cerr << "Failed to register routes" << std::endl;
        return 1;
    }

    auto matcher = builder.Build();

    // Lookup a GET with variable capture
    std::vector<VariableBinding> bindings;
    Method found = matcher->Lookup("GET", "/v1/books/sci-fi/dune", &bindings);

    std::cout << "Found method pointer: " << found << std::endl;
    std::cout << "Bindings size: " << bindings.size() << std::endl;
    for (const auto& b : bindings) {
        std::cout << "Binding field path: ";
        for (size_t i = 0; i < b.field_path.size(); ++i) {
            if (i) std::cout << '.';
            std::cout << b.field_path[i];
        }
        std::cout << " value=" << b.value << std::endl;
    }

    // Simple negative test
    Method not_found = matcher->Lookup("DELETE", "/v1/books/123");
    std::cout << "Not found (should be 0): " << (not_found == nullptr) << std::endl;

    return 0;
}
