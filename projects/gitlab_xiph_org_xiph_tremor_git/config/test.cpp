#include <stdio.h>
#include <string.h>
#include <ivorbiscodec.h>
#include <ivorbisfile.h>

int main() {
    vorbis_info vi;
    vorbis_comment vc;

    vorbis_info_init(&vi);
    vorbis_comment_init(&vc);

    // Query functions should return empty/zero state on fresh structs
    int count = vorbis_comment_query_count(&vc, (char*)"ARTIST");
    char *val = vorbis_comment_query(&vc, (char*)"TITLE", 0);

    // Clear resources
    vorbis_comment_clear(&vc);
    vorbis_info_clear(&vi);

    // Exercise ov_* symbol to ensure libvorbisidec also links
    OggVorbis_File vf; 
    memset(&vf, 0, sizeof(vf));
    ov_clear(&vf);

    printf("tremor basic API test completed: count=%d, val=%p\n", count, (void*)val);
    return 0;
}
