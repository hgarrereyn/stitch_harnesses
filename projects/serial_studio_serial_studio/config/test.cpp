#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "/fuzz/install/include/kissfft/kiss_fft.h"

int main(){
    int n = 8;
    kiss_fft_cfg cfg = kiss_fft_alloc(n, 0, NULL, NULL);
    if(!cfg){
        printf("alloc failed\n");
        return 1;
    }
    kiss_fft_cpx in[8], out[8];
    for(int i=0;i<n;i++){ in[i].r = (float)i; in[i].i = 0.0f; }
    kiss_fft(cfg, in, out);
    printf("out0=(%f,%f)\n", out[0].r, out[0].i);
    free(cfg);
    return 0;
}
