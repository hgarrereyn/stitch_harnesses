#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <tensorrtx/utils.h>

int main() {
    std::cout << to_string_with_precision(3.14159f, 3) << "\n";

    const char* fname = "/tmp/labels.txt";
    {
        std::ofstream f(fname);
        f << "  class0\nclass1\n  class2  \n";
    }
    std::unordered_map<int, std::string> labels;
    read_labels(fname, labels);
    std::cout << labels[0] << "," << labels[1] << "," << labels[2] << "\n";

    std::vector<std::string> names;
    int ret = read_files_in_dir("/tmp", names);
    std::cout << "dir_ret=" << ret << ", count_ge_1=" << (names.size() >= 1) << "\n";
    return 0;
}
