#include <stdio.h>
#include <string.h>
#include <speex/speex.h>
#include <speex/speex_bits.h>

int main() {
    // Initialize bits
    SpeexBits bits;
    speex_bits_init(&bits);

    // Use narrowband mode
    const SpeexMode *mode = speex_lib_get_mode(SPEEX_MODEID_NB);
    if (!mode) {
        printf("Failed to get Speex mode\n");
        return 1;
    }

    // Create encoder and decoder states
    void *enc_state = speex_encoder_init(mode);
    void *dec_state = speex_decoder_init(mode);
    if (!enc_state || !dec_state) {
        printf("Failed to init encoder/decoder\n");
        return 1;
    }

    // Set a basic quality parameter on encoder
    int quality = 3;
    speex_encoder_ctl(enc_state, SPEEX_SET_QUALITY, &quality);

    // Prepare a tiny frame of silence (zeros)
    short in[160]; // 20ms at 8kHz for NB
    memset(in, 0, sizeof(in));

    // Encode one frame
    speex_bits_reset(&bits);
    speex_encode_int(enc_state, in, &bits);

    // Extract to a temporary buffer
    char out[200];
    int nbBytes = speex_bits_write(&bits, out, (int)sizeof(out));

    // Decode the frame back
    speex_bits_read_from(&bits, out, nbBytes);
    short decoded[160];
    int dec_ret = speex_decode_int(dec_state, &bits, decoded);

    // Cleanup
    speex_encoder_destroy(enc_state);
    speex_decoder_destroy(dec_state);
    speex_bits_destroy(&bits);

    printf("Encoded %d bytes, decode ret=%d, first sample=%d\n", nbBytes, dec_ret, (int)decoded[0]);
    return 0;
}
