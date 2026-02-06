#include <iostream>
extern "C" {
#include <opus/opusfile.h>
}
int main() {
    OpusTags tags;
    opus_tags_init(&tags);
    opus_tags_clear(&tags);
    OpusServerInfo info;
    opus_server_info_init(&info);
    opus_server_info_clear(&info);
    std::cout << "OK\n";
    return 0;
}
