#include <cstdio>
#include <cstddef>
#include <geos_c.h>

static void notice(const char* msg, void* userdata){ (void)userdata; fprintf(stderr, "GEOS notice: %s\n", msg); }
static void errorf(const char* msg, void* userdata){ (void)userdata; fprintf(stderr, "GEOS error: %s\n", msg); }

int main(){
    GEOSContextHandle_t ctx = GEOS_init_r();
    GEOSContext_setNoticeMessageHandler_r(ctx, notice, nullptr);
    GEOSContext_setErrorMessageHandler_r(ctx, errorf, nullptr);

    const char* wkt = "POLYGON((0 0, 1 0, 0 1, 0 0))";
    GEOSWKTReader* rdr = GEOSWKTReader_create_r(ctx);
    if(!rdr){ GEOS_finish_r(ctx); return 1; }
    GEOSGeometry* g = GEOSWKTReader_read_r(ctx, rdr, wkt);
    if(!g){ GEOSWKTReader_destroy_r(ctx, rdr); GEOS_finish_r(ctx); return 1; }

    double area = 0.0;
    if(!GEOSArea_r(ctx, g, &area)){
        GEOSGeom_destroy_r(ctx, g);
        GEOSWKTReader_destroy_r(ctx, rdr);
        GEOS_finish_r(ctx);
        return 1;
    }

    printf("Area: %.3f\n", area);

    GEOSGeom_destroy_r(ctx, g);
    GEOSWKTReader_destroy_r(ctx, rdr);
    GEOS_finish_r(ctx);
    return 0;
}
