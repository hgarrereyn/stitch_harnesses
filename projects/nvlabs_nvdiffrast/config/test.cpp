#include <iostream>
#include <nvdiffrast/texture.h>

int main() {
    TextureKernelParams p{};
    p.texWidth = 8;
    p.texHeight = 4;
    p.channels = 3;
    p.boundaryMode = TEX_BOUNDARY_MODE_CLAMP;
    p.mipLevelLimit = 16;

    int offsets[TEX_MAX_MIP_LEVEL] = {0};
    int total = calculateMipInfo(p, offsets);

    std::cout << "mipLevelMax=" << p.mipLevelMax << ", totalElems=" << total << "\n";
    p.texWidth = 7; p.texHeight = 3;
    raiseMipSizeError(p);
    std::cout << "done\n";
    return 0;
}
