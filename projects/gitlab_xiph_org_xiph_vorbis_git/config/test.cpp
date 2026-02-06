#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>
#include <stdio.h>

int main() {
    // Basic sanity: init/clear info and comment structs
    vorbis_info vi; 
    vorbis_comment vc;
    vorbis_info_init(&vi);
    vorbis_comment_init(&vc);
    vorbis_comment_add_tag(&vc, "ENCODER", "fuzz-setup-test");

    // Set up simple encoder configuration (won't actually encode)
    int ret = vorbis_encode_init_vbr(&vi, 2, 44100, 0.4f);
    printf("encode init ret=%d, rate=%ld, channels=%d\n", ret, (long)vi.rate, vi.channels);

    vorbis_comment_clear(&vc);
    vorbis_info_clear(&vi);

    // libvorbisfile small sanity: just check the version string accessor exists
    const char* ver = vorbis_version_string();
    printf("vorbis version: %s\n", ver ? ver : "(null)");

    return 0;
}
