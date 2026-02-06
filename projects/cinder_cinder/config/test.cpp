#include "cinder/Rand.h"
#include "cinder/Color.h"
#include <iostream>

int main() {
    cinder::Rand rng;
    float v = rng.nextFloat();
    cinder::Colorf col(v, 1.0f - v, 0.5f);
    std::cout << "rand=" << v << ", color=" << col.r << "," << col.g << "," << col.b << std::endl;
    return 0;
}
