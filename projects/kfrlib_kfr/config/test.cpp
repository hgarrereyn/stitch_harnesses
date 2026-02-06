#include <iostream>

namespace kfr {
const char* library_version_dft();
const char* library_version_dsp();
const char* library_version_io();
const char* library_version_audio();
const char* library_version_codecs();
}

int main() {
    std::cout << "dft=" << kfr::library_version_dft() << "\n";
    std::cout << "dsp=" << kfr::library_version_dsp() << "\n";
    std::cout << "io=" << kfr::library_version_io() << "\n";
    std::cout << "audio=" << kfr::library_version_audio() << ", codecs=" << kfr::library_version_codecs() << "\n";
    return 0;
}
