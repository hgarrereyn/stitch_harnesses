#include <iostream>
#include <cstring>
extern "C" {
#include "re.h"
}

int main() {
    // Compile a simple pattern and run a match
    const char *pattern = "^he.+o$"; // matches strings starting with he and ending with o
    const char *text = "hello";

    regex_t compiled[ MAX_REGEXP_OBJECTS ];
    unsigned char buffer[ MAX_CHAR_CLASS_LEN + 1 ];

    if (re_compile(pattern, std::strlen(pattern), compiled, buffer) != 0) {
        std::cout << "compile failed" << std::endl;
        return 1;
    }

    size_t matchlen = 0;
    int idx = re_matchp(compiled, text, std::strlen(text), std::strlen(text), &matchlen);

    std::cout << "match index: " << idx << ", length: " << matchlen << std::endl;
    return 0;
}
