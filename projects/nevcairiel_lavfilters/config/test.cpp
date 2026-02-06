#include <iostream>
#include <LAVAudioSettings.h>
int main() {
    LAVAudioCodec c = Codec_AAC;
    LAVAudioSampleFormat f = SampleFormat_FP32;
    std::cout << "Codec enum value: " << (int)c << ", format: " << (int)f << "\n";
    return 0;
}
