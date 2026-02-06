#include <cstdio>
extern "C" {
#include <cregex.h>
}

int main() {
    const char* pattern = "h.*o";
    cregex_node_t* ast = cregex_parse(pattern);
    if (!ast) {
        std::printf("parse failed\n");
        return 1;
    }
    cregex_program_t* prog = cregex_compile_node(ast);
    cregex_parse_free(ast);
    if (!prog) {
        std::printf("compile failed\n");
        return 1;
    }
    const char* matches[2] = {nullptr, nullptr};
    int rc = cregex_program_run(prog, "hello", matches, 2);
    std::printf("run rc=%d\n", rc);
    if (rc >= 1 && matches[0]) {
        std::printf("matched at: %s\n", matches[0]);
    }
    cregex_compile_free(prog);
    return 0;
}
