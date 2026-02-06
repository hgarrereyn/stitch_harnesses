#include <cstdio>
#include "imtui/imtui.h"

int main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if (!ImTui_ImplText_Init()) {
        printf("ImTui text init failed\n");
        return 1;
    }

    ImGui::NewFrame();
    ImGui::Begin("Hello ImTui");
    ImGui::Text("This is a test window rendered to a text buffer.");
    ImGui::End();
    ImGui::Render();

    ImTui::TScreen screen;
    screen.resize(80, 25);
    ImTui_ImplText_RenderDrawData(ImGui::GetDrawData(), &screen);

    int nonzero = 0;
    for (int i = 0; i < screen.size(); ++i) if (screen.data[i]) ++nonzero;
    printf("Rendered cells: %d\n", nonzero);

    ImTui_ImplText_Shutdown();
    ImGui::DestroyContext();
    return 0;
}
