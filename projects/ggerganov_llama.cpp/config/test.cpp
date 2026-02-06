#include <llama.h>
#include <iostream>

int main() {
    const char * info = llama_print_system_info();
    if (!info) info = "(null)";
    std::cout << "llama system info: " << info << std::endl;
    return 0;
}
