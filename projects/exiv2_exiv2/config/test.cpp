#include <iostream>
#include <exiv2/exiv2.hpp>

int main() {
    std::cout << "Exiv2 version: " << Exiv2::versionString() << "\n";

    Exiv2::ExifData exifData;
    exifData["Exif.Image.Software"] = std::string("exiv2_test");
    std::cout << "Exif entries: " << exifData.count() << "\n";

    for (const auto& md : exifData) {
        std::cout << md.key() << " = " << md.toString() << "\n";
    }
    return 0;
}
