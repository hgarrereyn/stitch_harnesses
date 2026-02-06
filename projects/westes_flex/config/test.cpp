#include <cstdio>
#include <iostream>
#include <FlexLexer.h>

extern "C" int yywrap(void);

int main() {
    int w = yywrap();
    FlexLexer* lex = nullptr;
    std::cout << "yywrap() returned: " << w << "\n";
    if (lex == nullptr) {
        std::cout << "FlexLexer header available." << std::endl;
    }
    return 0;
}
