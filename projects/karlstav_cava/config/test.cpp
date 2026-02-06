#include <iostream>
#include <vector>
#include <cmath>
extern "C" {
#include <cavacore.h>
}

int main() {
    int bars = 8;
    unsigned int rate = 44100;
    int channels = 1; // mono
    int autosens = 1;
    double noise_reduction = 0.77;
    int low_cut = 50;
    int high_cut = 10000;

    cava_plan* plan = cava_init(bars, rate, channels, autosens, noise_reduction, low_cut, high_cut);
    if (!plan || plan->status != 0) {
        std::cerr << "Failed to init cavacore: " << (plan ? plan->error_message : "null plan") << "\n";
        return 1;
    }

    int new_samples = 512;
    std::vector<double> in(new_samples * channels);
    double freq = 440.0;
    for (int i = 0; i < new_samples; ++i) {
        in[i] = std::sin(2.0 * M_PI * freq * (double)i / (double)rate);
    }

    std::vector<double> out(bars * channels, 0.0);
    cava_execute(in.data(), new_samples, out.data(), plan);

    std::cout << "Bars:";
    for (int i = 0; i < bars; ++i) {
        std::cout << ' ' << out[i];
    }
    std::cout << "\n";

    cava_destroy(plan);
    return 0;
}
