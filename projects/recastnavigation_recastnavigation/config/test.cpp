#include <DetourNavMesh.h>
#include <DetourStatus.h>
#include <iostream>

int main() {
    dtNavMeshParams params{};
    params.orig[0] = 0.0f; params.orig[1] = 0.0f; params.orig[2] = 0.0f;
    params.tileWidth = 10.0f;
    params.tileHeight = 10.0f;
    params.maxTiles = 1;
    params.maxPolys = 1;

    dtNavMesh nav;
    dtStatus st = nav.init(&params);
    if (dtStatusFailed(st)) {
        std::cout << "Failed to init navmesh" << std::endl;
        return 1;
    }
    float pos[3] = {5.0f, 0.0f, 5.0f};
    int tx = -1, ty = -1;
    nav.calcTileLoc(pos, &tx, &ty);
    std::cout << "Tile loc: (" << tx << ", " << ty << ")" << std::endl;
    return 0;
}
