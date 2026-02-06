#include <iostream>
#include <vector>
#include "opentype-sanitiser.h"
#include "ots-memory-stream.h"

int main() {
    // Use the public API: create a MemoryStream and write some values
    std::vector<unsigned char> buf(32);
    ots::MemoryStream ms(buf.data(), buf.size());
    ms.WriteU32(OTS_TAG('t','e','s','t'));
    ms.Pad(8);
    std::cout << "MemoryStream tell: " << ms.Tell() << ", checksum: " << ms.chksum() << "\n";
    return 0;
}
