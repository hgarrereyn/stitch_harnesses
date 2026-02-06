#include <imgui.h>
#include <implot.h>
#include <iostream>

int main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    const ImPlotInputMap& map = ImPlot::GetInputMap();
    const ImPlotStyle& style = ImPlot::GetStyle();

    std::cout << "PanMod=" << map.PanMod << ", UseLocalTime=" << (style.UseLocalTime ? 1 : 0) << std::endl;

    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    return 0;
}
