#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>
#include <cstdint>
#include <vector>
#include <cstdio>

int main() {
    // Minimal 16-bit PCM mono WAV with a single zero sample at 8000 Hz.
    const unsigned char wavData[] = {
        'R','I','F','F',
        0x26,0x00,0x00,0x00, // ChunkSize = 38 (36 + Subchunk2Size)
        'W','A','V','E',
        'f','m','t',' ',
        16,0,0,0,            // Subchunk1Size = 16 for PCM
        1,0,                 // AudioFormat = 1 (PCM)
        1,0,                 // NumChannels = 1
        0x40,0x1F,0x00,0x00, // SampleRate = 8000
        0x80,0x3E,0x00,0x00, // ByteRate = 16000
        2,0,                 // BlockAlign = 2
        16,0,                // BitsPerSample = 16
        'd','a','t','a',
        2,0,0,0,             // Subchunk2Size = 2 bytes (1 frame)
        0x00,0x00            // Sample data: 0
    };

    drwav wav{};
    if (!drwav_init_memory(&wav, wavData, sizeof(wavData), nullptr)) {
        return 1; // Failed to parse WAV
    }

    std::vector<int16_t> samples(static_cast<size_t>(wav.totalPCMFrameCount * wav.channels));
    size_t framesRead = drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, samples.data());

    drwav_uninit(&wav);

    // Expect to read at least 1 frame.
    if (framesRead == 0) return 2;

    // Print something small to ensure program did something.
    std::printf("Frames: %zu, Channels: %u\n", framesRead, wav.channels);
    return 0;
}
