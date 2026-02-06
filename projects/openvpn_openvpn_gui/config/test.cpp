#include <cstdio>
#include <cstdint>
#include <cstring>
#include <vector>
extern "C" {
#include <qrcodegen/qrcodegen.h>
}

int main() {
    const char *text = "OpenVPN-GUI QR Test";
    std::vector<uint8_t> qrcode(qrcodegen_BUFFER_LEN_MAX);
    std::vector<uint8_t> temp(qrcodegen_BUFFER_LEN_MAX);

    bool ok = qrcodegen_encodeText(text, temp.data(), qrcode.data(),
                                   qrcodegen_Ecc_LOW, qrcodegen_VERSION_MIN,
                                   qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (!ok) {
        std::printf("encode failed\n");
        return 1;
    }
    int size = qrcodegen_getSize(qrcode.data());
    int black = 0;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (qrcodegen_getModule(qrcode.data(), x, y)) black++;
        }
    }
    std::printf("QR size=%d, black=%d\n", size, black);
    return 0;
}
