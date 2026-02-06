#include <imgui.h>
#include <cstdio>

int main() {
    ImGuiContext* ctx = ImGui::CreateContext();
    if (!ctx) {
        std::printf("Failed to create ImGui context\n");
        return 1;
    }
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(640, 480);

    // Build font atlas to satisfy NewFrame assertions without a renderer backend
    unsigned char* pixels = nullptr; int width = 0, height = 0;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    ImGui::NewFrame();
    ImGui::Text("Hello, ImGui!");
    ImGui::EndFrame();

    ImGui::DestroyContext(ctx);
    std::printf("ImGui basic test completed.\n");
    return 0;
}
