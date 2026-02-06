#include <qrencode.h>
#include <cstdio>
#include <cstdlib>

int main() {
    int maj=0, min=0, mic=0;
    QRcode_APIVersion(&maj, &min, &mic);
    QRcode *code = QRcode_encodeString8bit("hello fuzzing", 0, QR_ECLEVEL_M);
    if (!code) {
        std::printf("Failed to encode string\n");
        return 1;
    }
    std::printf("libqrencode %d.%d.%d: Generated QR width=%d, version=%d\n", maj, min, mic, code->width, code->version);
    long sum = 0;
    for (int i = 0; i < code->width && i < 32; ++i) sum += code->data[i];
    std::printf("Data checksum(partial)=%ld\n", sum);
    QRcode_free(code);
    return 0;
}
