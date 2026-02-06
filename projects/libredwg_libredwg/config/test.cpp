#include <cstdio>
#include "dwg_api.h"

int main() {
    bool isEnt = is_dwg_entity("LINE");
    bool isObj = is_dwg_object("LAYER");
    int line_size = dwg_dynapi_fields_size("LINE");
    std::printf("is_dwg_entity(LINE)=%d\n", (int)isEnt);
    std::printf("is_dwg_object(LAYER)=%d\n", (int)isObj);
    std::printf("fields_size(LINE)=%d\n", line_size);
    return 0;
}
