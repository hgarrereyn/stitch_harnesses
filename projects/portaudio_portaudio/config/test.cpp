#include <cstdio>
#include <portaudio.h>

int main() {
    const char* ver = Pa_GetVersionText();
    if(!ver) ver = "unknown";
    std::printf("PortAudio version: %s\n", ver);
    return 0;
}
