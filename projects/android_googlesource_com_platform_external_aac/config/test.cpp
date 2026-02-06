#include <stdio.h>
#include "aacdecoder_lib.h"

int main() {
    HANDLE_AACDECODER dec = aacDecoder_Open(TT_MP4_RAW, 1);
    if (dec) {
        aacDecoder_Close(dec);
        printf("Decoder open/close OK.\n");
    } else {
        printf("Decoder open failed.\n");
    }
    return 0;
}
