#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <brotli/encode.h>
#include <brotli/decode.h>

int main() {
    const char* input = "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
    size_t input_size = strlen(input);

    size_t max_compressed = BrotliEncoderMaxCompressedSize(input_size);
    uint8_t* compressed = (uint8_t*)malloc(max_compressed);
    if (!compressed) return 1;

    size_t encoded_size = max_compressed;
    BROTLI_BOOL ok = BrotliEncoderCompress(
        /*quality=*/5,
        /*lgwin=*/22,
        /*mode=*/BROTLI_MODE_GENERIC,
        /*input_size=*/input_size,
        (const uint8_t*)input,
        &encoded_size,
        compressed);
    if (!ok) {
        fprintf(stderr, "Compression failed\n");
        free(compressed);
        return 1;
    }

    uint8_t* decompressed = (uint8_t*)malloc(input_size + 1);
    if (!decompressed) {
        free(compressed);
        return 1;
    }
    size_t decoded_size = input_size;
    BrotliDecoderResult res = BrotliDecoderDecompress(
        encoded_size, compressed, &decoded_size, decompressed);

    if (res != BROTLI_DECODER_RESULT_SUCCESS || decoded_size != input_size) {
        fprintf(stderr, "Decompression failed\n");
        free(compressed);
        free(decompressed);
        return 1;
    }

    decompressed[decoded_size] = '\0';
    printf("%s\n", (char*)decompressed);

    free(compressed);
    free(decompressed);
    return 0;
}
