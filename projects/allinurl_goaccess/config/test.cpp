extern "C" {
#include <stdint.h>
#include <base64.h>
#include <bitmap.h>
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *msg = "hello";
    char *enc = base64_encode(msg, 5);
    if (!enc) return 1;
    size_t out_len = 0;
    char *dec = base64_decode(enc, &out_len);
    if (!dec) return 1;

    bitmap *bm = bitmap_create(16);
    if (!bm) return 1;
    bitmap_set_bit((word_t*)bm->bmp, 3);
    int has = bitmap_key_exists(bm, 3);

    printf("enc=%s dec_len=%zu has=%d\n", enc, out_len, has);

    free(enc);
    free(dec);
    free_bitmap(bm);
    return 0;
}
