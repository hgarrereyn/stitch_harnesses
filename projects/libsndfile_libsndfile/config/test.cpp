#include <sndfile.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char *path = "/tmp/test.wav";
    short samples[480];
    for (int i = 0; i < 480; ++i) samples[i] = (short)((i % 96) * 300 - 14400);

    SF_INFO info;
    memset(&info, 0, sizeof(info));
    info.samplerate = 48000;
    info.channels = 1;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE *snd = sf_open(path, SFM_WRITE, &info);
    if (!snd) {
        fprintf(stderr, "sf_open write failed: %s\n", sf_strerror(NULL));
        return 1;
    }
    sf_count_t written = sf_write_short(snd, samples, (sf_count_t)(sizeof(samples)/sizeof(samples[0])));
    sf_close(snd);

    if (written <= 0) {
        fprintf(stderr, "write failed\n");
        return 1;
    }

    // Read back
    SF_INFO rinfo;
    memset(&rinfo, 0, sizeof(rinfo));
    SNDFILE *sndr = sf_open(path, SFM_READ, &rinfo);
    if (!sndr) {
        fprintf(stderr, "sf_open read failed: %s\n", sf_strerror(NULL));
        return 1;
    }
    short rb[480];
    sf_count_t rd = sf_read_short(sndr, rb, 480);
    sf_close(sndr);

    if (rd <= 0) {
        fprintf(stderr, "read failed\n");
        return 1;
    }

    printf("ok %ld samples read back\n", (long)rd);
    return 0;
}
