#include <stdio.h>
#include <ual.h>
int main(){
    int v = ual_version();
    int s = ual_add(2, 3);
    printf("ual_version=%d sum=%d\n", v, s);
    return 0;
}
