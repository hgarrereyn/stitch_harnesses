#include <netcdf.h>
#include <stdio.h>

int main() {
    int ncid, dimid, varid;
    const char* path = "/tmp/test_nc.nc";
    int retval = nc_create(path, NC_CLOBBER | NC_64BIT_OFFSET, &ncid);
    if (retval) { printf("nc_create failed: %s\n", nc_strerror(retval)); return 0; }

    if ((retval = nc_def_dim(ncid, "x", 4, &dimid))) {
        printf("nc_def_dim failed: %s\n", nc_strerror(retval));
        nc_close(ncid); return 0;
    }
    int dims[1] = {dimid};
    if ((retval = nc_def_var(ncid, "v", NC_INT, 1, dims, &varid))) {
        printf("nc_def_var failed: %s\n", nc_strerror(retval));
        nc_close(ncid); return 0;
    }
    if ((retval = nc_enddef(ncid))) { printf("nc_enddef failed: %s\n", nc_strerror(retval)); nc_close(ncid); return 0; }

    int data[4] = {1,2,3,4};
    if ((retval = nc_put_var_int(ncid, varid, data))) {
        printf("nc_put_var_int failed: %s\n", nc_strerror(retval));
    }
    nc_close(ncid);
    printf("Created %s successfully.\n", path);
    return 0;
}
