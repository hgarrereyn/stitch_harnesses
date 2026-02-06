#include <MNN/Tensor.hpp>
#include <MNN/MNNDefine.h>
#include <vector>
#include <iostream>

int main() {
    std::cout << "MNN version: " << MNN_VERSION << std::endl;
    std::vector<int> shape = {1, 2, 3, 4};
    MNN::Tensor* t = MNN::Tensor::create(shape, halide_type_of<float>(), nullptr, MNN::Tensor::TENSORFLOW);
    if (!t) {
        std::cout << "Tensor create failed" << std::endl;
        return 1;
    }
    t->printShape();
    std::cout << "Dims: " << t->dimensions() << ", size bytes: " << t->size() << std::endl;
    MNN::Tensor::destroy(t);
    return 0;
}
