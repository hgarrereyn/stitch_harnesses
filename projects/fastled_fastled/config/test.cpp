#include <FastLED.h>
#include <iostream>

int main() {
    const int NUM = 16;
    CRGB leds[NUM];
    for (int i = 0; i < NUM; ++i) {
        leds[i].setRGB((i * 7) & 0xFF, (i * 13) & 0xFF, (255 - i * 5) & 0xFF);
    }
    unsigned long long sum = 0;
    for (int i = 0; i < NUM; ++i) {
        sum += leds[i].r + leds[i].g + leds[i].b;
    }
    std::cout << "Checksum:" << sum << std::endl;
    return 0;
}
