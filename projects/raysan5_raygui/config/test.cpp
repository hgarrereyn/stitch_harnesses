#include <cstdio>
#define RAYGUI_STANDALONE
#include "raygui.h"

int main() {
    // Use only header-provided constants/types; no function calls required
    printf("raygui version: %s\n", RAYGUI_VERSION);
    // Touch a couple of enums/types to ensure header is usable
    GuiState s = STATE_NORMAL;
    (void)s;
    return 0;
}
