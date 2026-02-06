#include <cstdio>
#include <cstring>
#include "ultrahdr_api.h"

int main() {
    uhdr_codec_private_t* enc = uhdr_create_encoder();
    if (!enc) return 1;
    uhdr_error_info_t st = uhdr_enc_set_preset(enc, UHDR_USAGE_REALTIME);
    st = uhdr_enc_set_output_format(enc, UHDR_CODEC_JPG);
    uhdr_release_encoder(enc);

    uhdr_codec_private_t* dec = uhdr_create_decoder();
    if (!dec) return 1;
    st = uhdr_dec_set_out_img_format(dec, UHDR_IMG_FMT_32bppRGBA8888);
    st = uhdr_dec_set_out_color_transfer(dec, UHDR_CT_SRGB);
    uhdr_release_decoder(dec);

    printf("libultrahdr basic API test ok. Version: %s\n", UHDR_LIB_VERSION_STR);
    return 0;
}
