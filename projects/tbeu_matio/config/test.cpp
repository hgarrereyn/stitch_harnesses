#include <stdio.h>
#include <matio.h>

int main(){
    int maj=0, min=0, rel=0;
    Mat_GetLibraryVersion(&maj, &min, &rel);

    size_t dims[2] = {2,2};
    double data[4] = {1.0,2.0,3.0,4.0};
    matvar_t* var = Mat_VarCreate("A", MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dims, data, 0);
    if(var){
        Mat_VarFree(var);
    }

    mat_t* m = Mat_CreateVer("/tmp/test.mat", "MATIO test", MAT_FT_MAT5);
    if(m){
        Mat_Close(m);
    }

    printf("matio %d.%d.%d ok\n", maj, min, rel);
    return 0;
}
