#include <iostream>
#include <aubio/aubio.h>

int main() {
    // Simple sanity test: create a buffer and apply an A-weighting filter
    uint_t winsize = 256;
    uint_t sr = 44100;
    fvec_t *buf = new_fvec(winsize);
    if (!buf) { std::cerr << "new_fvec failed\n"; return 1; }

    // Fill with zeros
    for (uint_t i = 0; i < winsize; i++) buf->data[i] = 0.0f;

    aubio_filter_t *flt = new_aubio_filter_a_weighting(sr);
    if (!flt) { std::cerr << "new_aubio_filter_a_weighting failed\n"; del_fvec(buf); return 1; }

    aubio_filter_do(flt, buf);

    // Create and delete another common object to ensure symbols link
    aubio_fft_t *fft = new_aubio_fft(winsize);
    if (!fft) { std::cerr << "new_aubio_fft failed\n"; del_aubio_filter(flt); del_fvec(buf); return 1; }

    // Cleanup
    del_aubio_fft(fft);
    del_aubio_filter(flt);
    del_fvec(buf);

    std::cout << "aubio basic test OK\n";
    return 0;
}
