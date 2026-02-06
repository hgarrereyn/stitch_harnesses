#include <iostream>
#include "clip.h"

int main() {
    // Basic smoke test for the clip library API
    std::cout << "clip test start\n";

    const int w = 2, h = 2;
    unsigned char pixels[w * h * 4] = {
        255, 0, 0, 255,   0, 255, 0, 255,
        0, 0, 255, 255,   255, 255, 0, 255
    };
    clip::image_spec spec;
    spec.width = w;
    spec.height = h;
    spec.bits_per_pixel = 32;
    spec.bytes_per_row = w * 4;
    spec.red_mask   = 0x000000ff;
    spec.green_mask = 0x0000ff00;
    spec.blue_mask  = 0x00ff0000;
    spec.alpha_mask = 0xff000000;

    clip::image img(pixels, spec);

    bool ok_img = clip::set_image(img);
    bool ok_txt = clip::set_text("hello");

    std::string txt;
    bool has_txt = clip::get_text(txt);

    std::cout << "set_image: " << ok_img << ", set_text: " << ok_txt
              << ", get_text: " << has_txt << ", text: '" << txt << "'\n";

    std::cout << "clip test done\n";
    return 0;
}
