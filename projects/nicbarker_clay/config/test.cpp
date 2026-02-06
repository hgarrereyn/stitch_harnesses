#include <cstdlib>
#include <cstdio>
#include <cstdint>

// Include the C++17 compatibility wrapper for clay
#include <clay_compat.h>

static void ErrorHandler(Clay_ErrorData errorData) {
    if (errorData.errorText.length > 0 && errorData.errorText.chars) {
        fwrite(errorData.errorText.chars, 1, (size_t)errorData.errorText.length, stdout);
        fputc('\n', stdout);
    }
}

static Clay_Dimensions MeasureTextShim(Clay_StringSlice text, Clay_TextElementConfig *config, void * /*userData*/) {
    Clay_Dimensions d; d.width = (float)text.length; d.height = (float)(config ? config->fontSize : 12);
    return d;
}

int main() {
    uint32_t minSize = Clay_MinMemorySize();
    void *mem = std::malloc(minSize);
    if (!mem) return 1;

    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(minSize, mem);
    Clay_ErrorHandler eh; eh.errorHandlerFunction = ErrorHandler; eh.userData = 0;

    Clay_Context* ctx = Clay_Initialize(arena, (Clay_Dimensions){ 640, 480 }, eh);
    if (!ctx) { std::free(mem); return 0; }

    Clay_SetMeasureTextFunction(MeasureTextShim, 0);

    Clay_SetLayoutDimensions((Clay_Dimensions){ 640, 480 });
    Clay_SetPointerState((Clay_Vector2){ 0, 0 }, false);
    Clay_UpdateScrollContainers(false, (Clay_Vector2){ 0, 0 }, 0.016f);

    Clay_BeginLayout();
    Clay_RenderCommandArray cmds = Clay_EndLayout();
    printf("render_cmds=%u\n", cmds.length);

    std::free(mem);
    return 0;
}
