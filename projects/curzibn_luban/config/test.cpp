#include <cstdio>
#include <turbojpeg.h>

extern "C" int luban_stub_version(void);

int main(){
    tjhandle h = tjInitCompress();
    if(!h){
        printf("tjInitCompress failed: %s\n", tjGetErrorStr());
        return 0; // don't fail the test
    }
    tjDestroy(h);
    printf("stub=%d\n", luban_stub_version());
    return 0;
}
