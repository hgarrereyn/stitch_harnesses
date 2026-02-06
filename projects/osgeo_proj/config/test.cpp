#include <proj.h>
#include <cstdio>

int main() {
    PJ_CONTEXT* C = proj_context_create();
    if(!C) return 0;
    PJ* P = proj_create_crs_to_crs(C, "EPSG:4326", "EPSG:3857", nullptr);
    if(!P) {
        proj_context_destroy(C);
        return 0;
    }
    PJ* norm = proj_normalize_for_visualization(C, P);
    proj_destroy(P);
    P = norm ? norm : P;

    PJ_COORD a = proj_coord(12, 55, 0, 0);
    PJ_COORD b = proj_trans(P, PJ_FWD, a);

    std::printf("%.0f %.0f\n", b.xy.x, b.xy.y);

    proj_destroy(P);
    proj_context_destroy(C);
    return 0;
}
