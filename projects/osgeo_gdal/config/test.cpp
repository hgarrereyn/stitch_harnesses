#include <cstdio>
#include <gdal.h>
#include <ogr_api.h>
#include <ogr_srs_api.h>

int main(){
    GDALAllRegister();
    // Create a small in-memory raster using C API and MEM driver
    GDALDriverH drv = GDALGetDriverByName("MEM");
    if(!drv){
        printf("MEM driver not available\n");
        return 0;
    }
    GDALDatasetH ds = GDALCreate(drv, "", 8, 8, 1, GDT_Byte, nullptr);
    if(ds){
        GDALClose(ds);
    }

    // Simple OGR geometry usage (C API)
    OGRGeometryH hGeom = OGR_G_CreateGeometry(wkbPoint);
    if(hGeom){
        OGR_G_DestroyGeometry(hGeom);
    }

    printf("GDAL basic test completed.\n");
    return 0;
}
