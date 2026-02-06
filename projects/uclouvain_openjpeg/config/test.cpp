#include <cstdio>
extern "C" {
#include <openjpeg.h>
}
int main() {
    OPJ_BOOL has_threads = opj_has_thread_support();
    int ncpus = opj_get_num_cpus();
    std::printf("OpenJPEG thread support: %s, CPUs: %d\n", has_threads ? "yes" : "no", ncpus);
    opj_codec_t* codec = opj_create_decompress(OPJ_CODEC_J2K);
    if (!codec) {
        std::printf("Failed to create decoder\n");
        return 0;
    }
    opj_destroy_codec(codec);
    std::printf("Decoder created and destroyed successfully.\n");
    return 0;
}
