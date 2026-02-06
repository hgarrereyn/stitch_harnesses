#include <cstdio>
#include <cstring>
extern "C" {
#include "ecapture_utils.h"
}
int main(){
    const char* name = ecapture_project_name();
    int v = ecapture_answer();
    if(!name || std::strcmp(name, "ecapture")!=0) return 1;
    std::printf("%s %d\n", name, v);
    return 0;
}
