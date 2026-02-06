#include <GuiLite.h>
#include <cstdio>

int main() {
    // Use some header-only API that doesn't require adapter symbols
    c_rect r(0, 0, 100, 50);
    bool inside = r.pt_in_rect(10, 10);

    c_theme::add_color(COLOR_WND_FONT, GL_RGB(255, 0, 0));
    unsigned int col = c_theme::get_color(COLOR_WND_FONT);

    std::printf("inside=%d, color=0x%08X\n", (int)inside, col);
    return 0;
}
