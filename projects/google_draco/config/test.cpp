#include <iostream>
#include <vector>
#include "draco/compression/decode.h"
#include "draco/core/decoder_buffer.h"

int main() {
    // Create a tiny invalid bitstream and ensure we can call a Draco API.
    std::vector<unsigned char> data(1, 0);
    draco::DecoderBuffer buffer;
    buffer.Init(reinterpret_cast<const char*>(data.data()), data.size());

    auto geom_type_or = draco::Decoder::GetEncodedGeometryType(&buffer);
    if (geom_type_or.ok()) {
        std::cout << "Encoded geometry type: " << static_cast<int>(geom_type_or.value()) << "\n";
    } else {
        std::cout << "Failed to determine geometry type (as expected for dummy data).\n";
    }
    return 0;
}
