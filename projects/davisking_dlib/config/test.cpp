#include <dlib/config.h>
#include <dlib/matrix.h>
#include <dlib/rand.h>
#include <dlib/md5.h>
#include <dlib/base64.h>
#include <dlib/image_transforms.h>
#include <dlib/array2d.h>
#include <sstream>
#include <iostream>

int main() {
    // Simple use of a few dlib APIs
    dlib::rand rng;
    dlib::matrix<double,2,2> m;
    m = 1, 2,
        3, 4;
    auto mt = dlib::trans(m);

    // Create a tiny image and apply a simple transform
    dlib::array2d<unsigned char> img(4,4);
    for (long r=0; r<img.nr(); ++r)
        for (long c=0; c<img.nc(); ++c)
            img[r][c] = static_cast<unsigned char>((r*img.nc()+c) % 255);
    dlib::array2d<unsigned char> out;
    dlib::assign_image(out, img);
    dlib::equalize_histogram(out);

    // MD5 and base64 usage via streams
    std::string data = "hello dlib";
    std::string digest = dlib::md5(data);

    dlib::base64 b64;
    std::stringstream in(data);
    std::ostringstream enc;
    b64.encode(in, enc);

    std::cout << "mt(0,1)=" << mt(0,1) << " digest=" << digest.substr(0,6) << " b64=" << enc.str().substr(0,6) << "\n";
    return 0;
}
