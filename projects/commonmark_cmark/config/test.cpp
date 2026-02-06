#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <cmark.h>
}

int main() {
    const char* md = "# Hello\n\nThis is **cmark** test.\n\n- item 1\n- item 2\n";
    char* html = cmark_markdown_to_html(md, std::strlen(md), 0);
    if (!html) {
        std::puts("conversion failed");
        return 1;
    }
    std::puts(html);
    std::free(html);
    return 0;
}
