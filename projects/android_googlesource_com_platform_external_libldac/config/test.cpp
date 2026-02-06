#include <cstdio>
#include <cstring>
extern "C" {
#include <ldacBT.h>
#include <ldacBT_abr.h>
}

int main() {
    HANDLE_LDAC_BT h = ldacBT_get_handle();
    if (!h) { printf("ldacBT_get_handle failed\n"); return 0; }
    HANDLE_LDAC_ABR habr = ldac_ABR_get_handle();
    if (!habr) { printf("ldac_ABR_get_handle failed\n"); ldacBT_free_handle(h); return 0; }

    // Initialize ABR with 100ms interval
    ldac_ABR_Init(habr, 100);

    // Initialize encoder: MTU 1000, HQ, Stereo, 16-bit, 48kHz
    int rc = ldacBT_init_handle_encode(h, 1000, LDACBT_EQMID_HQ, LDACBT_CHANNEL_MODE_STEREO, LDACBT_SMPL_FMT_S16, 48000);
    if (rc != 0) {
        int err = ldacBT_get_error_code(h);
        printf("init failed err=%d\n", err);
        ldac_ABR_free_handle(habr);
        ldacBT_free_handle(h);
        return 0;
    }

    // Prepare one frame of silence: 128 samples per channel, 2 channels, S16 => 256 samples
    short pcm[128*2];
    memset(pcm, 0, sizeof(pcm));
    unsigned char out[LDACBT_MAX_NBYTES];
    int pcm_used = 0, out_sz = 0, nframes = 0;

    // Run ABR once (no effect in this simple test)
    (void)ldac_ABR_Proc(h, habr, 0U, 0U);

    int enc_rc = ldacBT_encode(h, pcm, &pcm_used, out, &out_sz, &nframes);
    int bitrate = ldacBT_get_bitrate(h);
    int sf = ldacBT_get_sampling_freq(h);

    printf("encode rc=%d used=%d out=%d frames=%d bitrate=%d sf=%d\n", enc_rc, pcm_used, out_sz, nframes, bitrate, sf);

    ldacBT_close_handle(h);
    ldac_ABR_free_handle(habr);
    ldacBT_free_handle(h);
    return 0;
}
