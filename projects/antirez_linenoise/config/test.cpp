#include <cstdio>
#include <cstring>
#include <cstdlib>
extern "C" {
#include <linenoise.h>
}

static void completion_cb(const char* prefix, linenoiseCompletions* lc) {
    (void)prefix;
    // Provide a couple of static completions regardless of prefix
    linenoiseAddCompletion(lc, "help");
    linenoiseAddCompletion(lc, "hello");
}

static char* hints_cb(const char* buf, int* color, int* bold) {
    (void)buf;
    if (color) *color = 35; // magenta
    if (bold) *bold = 0;
    char* hint = (char*)std::malloc(8);
    if (!hint) return NULL;
    std::snprintf(hint, 8, " hint");
    return hint;
}

static void free_hints_cb(void* ptr) {
    std::free(ptr);
}

int main() {
    // Set callbacks
    linenoiseSetCompletionCallback(&completion_cb);
    linenoiseSetHintsCallback(&hints_cb);
    linenoiseSetFreeHintsCallback(&free_hints_cb);

    // History and settings
    linenoiseHistorySetMaxLen(5);
    linenoiseHistoryAdd("first");
    linenoiseHistoryAdd("second");

    // Save and load history to a temp file
    const char* path = "/tmp/linenoise_test_hist";
    linenoiseHistorySave(path);
    linenoiseHistoryLoad(path);

    // Toggle some modes/utilities (non-blocking)
    linenoiseSetMultiLine(1);
    linenoiseMaskModeEnable();
    linenoiseMaskModeDisable();
    linenoiseClearScreen();

    std::printf("linenoise test setup complete. History and callbacks configured.\n");
    return 0;
}
