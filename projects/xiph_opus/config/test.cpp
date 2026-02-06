#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include <opus/opus.h>
}

int main() {
    int err;
    int sample_rate = 48000;
    int channels = 1;
    int application = OPUS_APPLICATION_AUDIO;

    OpusEncoder* enc = opus_encoder_create(sample_rate, channels, application, &err);
    if (err != OPUS_OK || !enc) {
        fprintf(stderr, "encoder create failed: %d\n", err);
        return 1;
    }

    OpusDecoder* dec = opus_decoder_create(sample_rate, channels, &err);
    if (err != OPUS_OK || !dec) {
        fprintf(stderr, "decoder create failed: %d\n", err);
        opus_encoder_destroy(enc);
        return 1;
    }

    const int frame_size = sample_rate/100; // 10 ms
    int16_t pcm_in[frame_size*channels];
    memset(pcm_in, 0, sizeof(pcm_in));

    unsigned char packet[4000];
    int nbBytes = opus_encode(enc, pcm_in, frame_size, packet, (opus_int32)sizeof(packet));
    if (nbBytes < 0) {
        fprintf(stderr, "encode failed: %d\n", nbBytes);
        opus_encoder_destroy(enc);
        opus_decoder_destroy(dec);
        return 1;
    }

    int16_t pcm_out[frame_size*channels];
    int decoded = opus_decode(dec, packet, nbBytes, pcm_out, frame_size, 0);
    if (decoded < 0) {
        fprintf(stderr, "decode failed: %d\n", decoded);
        opus_encoder_destroy(enc);
        opus_decoder_destroy(dec);
        return 1;
    }

    long sum = 0;
    for (int i = 0; i < decoded*channels; ++i) sum += pcm_out[i];
    printf("ok %ld\n", sum);

    opus_encoder_destroy(enc);
    opus_decoder_destroy(dec);
    return 0;
}
