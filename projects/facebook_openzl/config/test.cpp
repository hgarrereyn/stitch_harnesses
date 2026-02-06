#include <cstring>
#include <iostream>
#include "openzl/openzl.h"

int main() {
    const char* msg = "Hello OpenZL!";
    const size_t srcSize = std::strlen(msg);

    ZL_CCtx* cctx = ZL_CCtx_create();
    if (!cctx) { std::cerr << "Failed to create cctx\n"; return 1; }

    // Set required format version
    ZL_Report vr = ZL_CCtx_setParameter(cctx, ZL_CParam_formatVersion, (int)ZL_getDefaultEncodingVersion());
    if (ZL_isError(vr)) { std::cerr << "Failed to set format version\n"; ZL_CCtx_free(cctx); return 1; }

    size_t dstCap = ZL_compressBound(srcSize);
    std::string compressed(dstCap, '\0');

    ZL_Report cr = ZL_CCtx_compress(cctx, compressed.data(), compressed.size(), msg, srcSize);
    if (ZL_isError(cr)) {
        std::cerr << "Compression failed, code: " << (int)ZL_errorCode(cr) << "\n";
        ZL_CCtx_free(cctx);
        return 1;
    }
    size_t cSize = ZL_validResult(cr);

    // Get decompressed size and decompress
    ZL_Report drSize = ZL_getDecompressedSize(compressed.data(), cSize);
    if (ZL_isError(drSize)) { std::cerr << "GetDecompressedSize failed\n"; ZL_CCtx_free(cctx); return 1; }
    size_t outSize = ZL_validResult(drSize);

    std::string decompressed(outSize, '\0');
    ZL_Report dr = ZL_decompress(decompressed.data(), decompressed.size(), compressed.data(), cSize);
    if (ZL_isError(dr)) { std::cerr << "Decompression failed\n"; ZL_CCtx_free(cctx); return 1; }

    bool ok = (ZL_validResult(dr) == srcSize) && (std::memcmp(decompressed.data(), msg, srcSize) == 0);
    std::cout << (ok ? "OK" : "FAIL") << "\n";

    ZL_CCtx_free(cctx);
    return ok ? 0 : 1;
}
