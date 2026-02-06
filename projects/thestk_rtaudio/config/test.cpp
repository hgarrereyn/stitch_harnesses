#include <iostream>
#include <string>
#include <rtaudio/RtAudio.h>

int main() {
    auto errcb = [](RtAudioErrorType type, const std::string &msg) {
        std::cout << "RtAudio error (" << type << "): " << msg << "\n";
    };

    RtAudio audio(RtAudio::UNSPECIFIED, std::move(errcb));
    unsigned int count = audio.getDeviceCount();
    std::cout << "RtAudio device count: " << count << "\n";
    if (count > 0) {
        unsigned int defOut = audio.getDefaultOutputDevice();
        std::cout << "Default output device id: " << defOut << "\n";
    }
    return 0;
}
