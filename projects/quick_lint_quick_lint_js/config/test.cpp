#include <cstdio>
#include <cstring>
#include <quick-lint-js/c-api.h>

int main() {
    QLJS_Web_Demo_Document* doc = qljs_web_demo_create_document();
    const char* code = "function f(){ return x + 1; }"; // x is undefined
    qljs_web_demo_set_text(doc, code, strlen(code));
    qljs_web_demo_set_language_options(doc, (QLJS_Language_Options)0);

    const QLJS_Web_Demo_Diagnostic* diags = qljs_web_demo_lint(doc);
    int count = 0;
    for (const QLJS_Web_Demo_Diagnostic* it = diags; it->message && it->code[0]; ++it) {
        count++;
    }

    const char* const* locales = qljs_list_locales();
    int locale_count = 0; while (locales && locales[locale_count]) locale_count++;

    std::printf("Diagnostics: %d, Locales listed: %d\n", count, locale_count);
    qljs_web_demo_destroy_document(doc);
    return 0;
}
