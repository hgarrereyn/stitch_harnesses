#include <vector>
#include <cstdio>
#include <cmath>
#include "meshoptimizer.h"

struct Vertex { float x,y,z; };

int main() {
    std::vector<Vertex> vertices = {{0.f,0.f,0.f},{1.f,0.f,0.f},{0.f,1.f,0.f}};
    unsigned int indices_in[3] = {0,1,2};

    unsigned int indices[3] = {indices_in[0], indices_in[1], indices_in[2]};
    meshopt_optimizeVertexCache(indices, indices, 3, (unsigned)vertices.size());

    std::vector<Vertex> vout = vertices;
    meshopt_optimizeVertexFetch(vout.data(), indices, 3, vertices.data(), vertices.size(), sizeof(Vertex));

    size_t bound = meshopt_encodeIndexBufferBound(3, (unsigned)vertices.size());
    std::vector<unsigned char> encoded(bound);
    size_t enc_size = meshopt_encodeIndexBuffer(encoded.data(), encoded.size(), indices, 3);
    std::vector<unsigned int> decoded(3);
    int dec_res = meshopt_decodeIndexBuffer(decoded.data(), 3, encoded.data(), enc_size);

    printf("enc=%zu dec=%d first=%u\n", enc_size, dec_res, decoded[0]);
    return 0;
}
