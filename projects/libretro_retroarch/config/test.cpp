#include <stdio.h>
#include <audio/audio_mix.h>

int main() {
    float dst[8] = {0};
    float src[8] = {1,2,3,4,5,6,7,8};
    audio_mix_volume(dst, src, 0.5f, 8);
    float sum = 0.0f;
    for (int i=0;i<8;i++) sum += dst[i];
    printf("sum=%.2f\n", sum);
    return 0;
}
