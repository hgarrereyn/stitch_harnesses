#include <iostream>
#include "mvt.hpp"

int main() {
    mvt_tile tile;
    mvt_layer layer;
    layer.name = "test";
    layer.version = 2;
    layer.extent = 4096;

    mvt_feature feat;
    feat.type = mvt_point;
    // a single MoveTo to place a point
    feat.geometry.emplace_back(mvt_moveto, 10, 20);

    layer.features.push_back(feat);
    tile.layers.push_back(layer);

    std::string encoded = tile.encode();
    bool was_compressed = false;
    std::string msg = encoded;
    mvt_tile decoded;
    decoded.decode(msg, was_compressed);

    std::cout << "layers=" << decoded.layers.size() << " features="
              << (decoded.layers.empty() ? 0 : decoded.layers[0].features.size()) << "\n";
    return 0;
}
