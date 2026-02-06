#include <stdio.h>
#include <string.h>
#include <opus/opus.h>

int main() {
    int err = 0;
    OpusEncoder *enc = opus_encoder_create(48000, 1, OPUS_APPLICATION_AUDIO, &err);
    if (!enc || err != OPUS_OK) {
        printf("encoder_create failed: %d\n", err);
        return 0;
    }
    OpusDecoder *dec = opus_decoder_create(48000, 1, &err);
    if (!dec || err != OPUS_OK) {
        printf("decoder_create failed: %d\n", err);
        opus_encoder_destroy(enc);
        return 0;
    }

    opus_int16 in[960]; // 20ms @ 48kHz mono
    memset(in, 0, sizeof(in));
    unsigned char packet[4000];

    int nbBytes = opus_encode(enc, in, 960, packet, (opus_int32)sizeof(packet));
    if (nbBytes < 0) {
        printf("encode error: %d\n", nbBytes);
        opus_decoder_destroy(dec);
        opus_encoder_destroy(enc);
        return 0;
    }

    opus_int16 out[960];
    int frame_size = opus_decode(dec, packet, nbBytes, out, 960, 0);
    if (frame_size < 0) {
        printf("decode error: %d\n", frame_size);
    } else {
        printf("encoded %d bytes, decoded %d samples\n", nbBytes, frame_size);
    }

    opus_decoder_destroy(dec);
    opus_encoder_destroy(enc);
    return 0;
}
