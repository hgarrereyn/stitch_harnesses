#include <iostream>
#include <string>
#include "crow.h"

int main() {
    crow::SimpleApp app; // construct app (won't run)

    // JSON build
    crow::json::wvalue obj({{"message", "Hello, World!"}});
    obj["number"] = 42;

    // Create a response and manipulate headers/body
    crow::response res;
    res.code = 200;
    res.add_header("Content-Type", "application/json");
    res.body = obj.dump();

    // Use mustache templating minimal example
    crow::mustache::context ctx;
    ctx["name"] = std::string("Crow");
    auto tmpl = crow::mustache::compile("Hello {{name}}!");
    auto rendered = tmpl.render(ctx);

    std::cout << "Rendered: " << rendered.dump() << "\n";
    std::cout << "Response size: " << res.body.size() << " bytes\n";
    return 0;
}
