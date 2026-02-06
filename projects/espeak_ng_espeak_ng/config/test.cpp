#include <espeak-ng/speak_lib.h>
#include <cstring>
#include <cstdio>

int main() {
    const char* data_path = "/fuzz/install/share/espeak-ng-data";
    int samplerate = espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, data_path, 0);
    if (samplerate <= 0) {
        std::printf("espeak_Initialize failed\n");
        return 0; // don't fail hard in CI
    }
    espeak_SetVoiceByName("en");
    const char* text = "Hello from eSpeak NG.";
    espeak_ERROR err = espeak_Synth(text, std::strlen(text) + 1, 0, POS_CHARACTER, 0, 0, nullptr, nullptr);
    if (err != EE_OK) {
        std::printf("espeak_Synth error %d\n", (int)err);
    }
    espeak_Synchronize();
    return 0;
}
