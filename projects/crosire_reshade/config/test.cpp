#include <iostream>
#include <string>
#include "effect_preprocessor.hpp"

int main() {
    reshadefx::preprocessor pp;
    pp.add_macro_definition("FOO", "42");
    const std::string src = "#if FOO == 42\nint x = FOO;\n#else\nint x = 0;\n#endif\n";
    if (!pp.append_string(src, "test.fx")) {
        std::cout << "Preprocess errors:\n" << pp.errors() << std::endl;
        return 1;
    }
    std::cout << "Output:\n" << pp.output() << std::endl;
    if (pp.output().find("42") == std::string::npos) return 2;
    return 0;
}
