#include <cstdio>
#include <ncnn/net.h>
#include <ncnn/mat.h>
#include <ncnn/c_api.h>

int main() {
    // Use C API to fetch version info
    const char* ver = ncnn_version();
    int vernum = ncnn_version_number();

    // Simple Mat usage
    ncnn::Mat a(8, 8); // 2D mat 8x8 float32
    a.fill(1.0f);
    ncnn::Mat b = a.clone();

    // Create an empty Net and an Extractor
    ncnn::Net net;
    net.opt.num_threads = 1;
    auto ex = net.create_extractor();
    ex.set_light_mode(true);

    // Touch a few fields to ensure symbols are linked
    size_t total = b.total();

    std::printf("ncnn version: %s (%d) total=%zu\n", ver ? ver : "(null)", vernum, total);
    return 0;
}
