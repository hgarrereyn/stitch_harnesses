#include <cstdio>
#include <cstdint>
#include <sysmodule/source/rtsp/RTSP.h>
#include <sysmodule/source/rtsp/RTP.h>

uint16_t SequenceNumbers[2] = {0,0};

int main() {
    char header[RTPHeaderSz] = {0};
    RTP_InitializeSequenceNumbers();
    RTP_PrepareHeader(header, 12345, true, STREAM_VIDEO);

    extern _Atomic bool RTSP_ClientStreaming;
    (void)RTSP_ClientStreaming;

    std::printf("RTP header first bytes: %02X %02X\n", (unsigned char)header[0], (unsigned char)header[1]);
    return 0;
}
