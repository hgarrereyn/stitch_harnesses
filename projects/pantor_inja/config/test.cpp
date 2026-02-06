#include <iostream>
#include <inja/inja.hpp>

int main() {
    // Prepare data
    nlohmann::json data;
    data["name"] = "world";

    // Render a simple template
    std::string result = inja::render("Hello {{ name }}!", data);
    std::cout << result << std::endl;

    // Use an environment
    inja::Environment env;
    inja::Template temp = env.parse("{{ upper(name) }}");
    std::string res2 = env.render(temp, data);
    std::cout << res2 << std::endl;

    return 0;
}
