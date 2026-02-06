#include <iostream>
#include <wavpack/wavpack.h>

int main() {
    const char *ver = WavpackGetLibraryVersionString();
    unsigned ver_num = WavpackGetLibraryVersion();
    std::cout << "WavPack library version: " << (ver ? ver : "unknown")
              << " (" << ver_num << ")\n";
    // Simple check to use a couple more API calls (no context required)
    int sr = WavpackGetNativeSampleRate(NULL); // should be 0 for NULL context
    int ch = WavpackGetNumChannels(NULL);      // should be 0 for NULL context
    std::cout << "SampleRate: " << sr << ", Channels: " << ch << "\n";
    return 0;
}
