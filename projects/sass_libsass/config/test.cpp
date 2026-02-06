#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sass/context.h>

int main() {
    const char* scss = "$color: red;\nbody { color: $color; }\n";
    // libsass takes ownership of the input buffer for data contexts
    char* input = (char*)std::malloc(std::strlen(scss) + 1);
    if (!input) return 1;
    std::strcpy(input, scss);

    // Create data context and options
    Sass_Data_Context* data_ctx = sass_make_data_context(input);
    if (!data_ctx) return 1;
    Sass_Options* opts = sass_make_options();
    // Example option: set nested output style
    sass_option_set_output_style(opts, SASS_STYLE_NESTED);
    sass_data_context_set_options(data_ctx, opts);

    // Compile
    int status = sass_compile_data_context(data_ctx);
    Sass_Context* ctx = sass_data_context_get_context(data_ctx);

    if (status != 0) {
        const char* err = sass_context_get_error_text(ctx);
        if (err) {
            std::printf("libsass compile error: %s\n", err);
        }
        sass_delete_data_context(data_ctx);
        sass_delete_options(opts);
        return 0; // still exit successfully for the test
    }

    const char* out = sass_context_get_output_string(ctx);
    if (out) {
        std::printf("Output CSS:\n%s\n", out);
    }

    // Cleanup
    sass_delete_data_context(data_ctx);
    sass_delete_options(opts);
    return 0;
}
