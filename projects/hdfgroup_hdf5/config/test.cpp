#include <hdf5.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *fname = "/tmp/hdf5_test_minimal.h5";
    hid_t file = H5Fcreate(fname, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file < 0) { fprintf(stderr, "H5Fcreate failed\n"); return 1; }

    hsize_t dims[1] = {4};
    hid_t space = H5Screate_simple(1, dims, NULL);
    if (space < 0) { fprintf(stderr, "H5Screate_simple failed\n"); return 1; }

    hid_t dset = H5Dcreate2(file, "d", H5T_NATIVE_INT, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset < 0) { fprintf(stderr, "H5Dcreate2 failed\n"); return 1; }

    int data[4] = {1,2,3,4};
    if (H5Dwrite(dset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data) < 0) {
        fprintf(stderr, "H5Dwrite failed\n");
        return 1;
    }

    H5Dclose(dset);
    H5Sclose(space);
    H5Fclose(file);

    file = H5Fopen(fname, H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file < 0) { fprintf(stderr, "H5Fopen failed\n"); return 1; }
    dset = H5Dopen2(file, "d", H5P_DEFAULT);
    if (dset < 0) { fprintf(stderr, "H5Dopen2 failed\n"); return 1; }
    int data2[4] = {0};
    if (H5Dread(dset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data2) < 0) {
        fprintf(stderr, "H5Dread failed\n");
        return 1;
    }
    if (data2[0] != 1) { fprintf(stderr, "Unexpected value: %d\n", data2[0]); return 1; }
    H5Dclose(dset);
    H5Fclose(file);

    printf("OK\n");
    return 0;
}
