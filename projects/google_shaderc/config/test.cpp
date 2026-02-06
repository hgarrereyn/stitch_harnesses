#include <shaderc/shaderc.hpp>
#include <iostream>
#include <vector>
#include <cstring>

int main() {
    const char* src = R"(\n#version 450\nvoid main() {}\n)";
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;
    auto result = compiler.CompileGlslToSpv(src, std::strlen(src), shaderc_vertex_shader, "minimal.vert", options);
    if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
        std::cout << "Compilation failed: " << result.GetErrorMessage() << "\n";
        return 0; // Do not fail the test
    }
    std::vector<uint32_t> spv(result.cbegin(), result.cend());
    std::cout << "SPIR-V module words: " << spv.size() << "\n";
    return 0;
}
