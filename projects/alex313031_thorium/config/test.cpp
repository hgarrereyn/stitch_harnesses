#include <iostream>
extern "C" {
#include <pak_defs.h>
#include <pak_header.h>
#include <pak_file.h>
#include <pak_pack.h>
}

int main() {
    // Prepare a minimal valid v4 pak in memory with 1 resource
    MyPakHeader hdr{};
    hdr.version = 4;            // v4 header
    hdr.resource_count = 1;     // one resource
    hdr.encoding = 0;           // no encoding
    hdr.alias_count = 0;        // ignored for v4
    hdr.size = PAK_HEADER_SIZE_V4;

    const uint32_t entrySize = (hdr.resource_count + 1) * PAK_ENTRY_SIZE; // +1 sentinel
    const uint32_t aliasSize = 0; // v4 has no alias table
    const uint32_t payloadSize = 8;
    const uint32_t headerSize = hdr.size;
    const uint32_t total = headerSize + entrySize + aliasSize + payloadSize;

    std::string buf(total, '\0');

    // Write header
    unsigned int wrote = pakWriteHeader(&hdr, buf.data());
    if (wrote != hdr.size) {
        std::cerr << "pakWriteHeader failed" << std::endl;
        return 1;
    }

    // Layout pointers
    PakEntry* entries = reinterpret_cast<PakEntry*>(buf.data() + headerSize);
    uint8_t* payload = reinterpret_cast<uint8_t*>(buf.data() + headerSize + entrySize + aliasSize);

    // Fill payload
    for (uint32_t i = 0; i < payloadSize; ++i) payload[i] = static_cast<uint8_t>(i);

    // Fill entries: first real, then sentinel
    entries[0].resource_id = 1;
    entries[0].offset = static_cast<uint32_t>(payload - reinterpret_cast<uint8_t*>(buf.data()));
    entries[1].resource_id = 0;
    entries[1].offset = entries[0].offset + payloadSize;

    // Validate format
    if (!pakCheckFormat(reinterpret_cast<uint8_t*>(buf.data()), total)) {
        std::cerr << "pakCheckFormat returned false" << std::endl;
        return 1;
    }

    // Retrieve the file by id
    PakFile f = pakGetFile(reinterpret_cast<uint8_t*>(buf.data()), 1);
    if (f.buffer == nullptr || f.size != payloadSize) {
        std::cerr << "pakGetFile failed" << std::endl;
        return 1;
    }

    // Simple check of content
    uint8_t* fb = reinterpret_cast<uint8_t*>(f.buffer);
    for (uint32_t i = 0; i < payloadSize; ++i) {
        if (fb[i] != i) {
            std::cerr << "payload mismatch at " << i << std::endl;
            return 1;
        }
    }

    std::cout << "pak library test passed: size=" << f.size << std::endl;
    return 0;
}
