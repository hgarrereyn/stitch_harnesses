#include <vector>
#include <cstring>
#include <iostream>
#include "libHDiffPatch/HDiff/diff.h"
#include "libHDiffPatch/HPatch/patch.h"

int main() {
    const char* oldStr = "Hello HDiffPatch!";
    const char* newStr = "Hello HDiffPatch!!"; // one extra '!'
    std::vector<unsigned char> oldData(strlen(oldStr));
    std::vector<unsigned char> newData(strlen(newStr));
    std::memcpy(oldData.data(), oldStr, oldData.size());
    std::memcpy(newData.data(), newStr, newData.size());

    std::vector<unsigned char> diff;
    create_diff(newData.data(), newData.data()+newData.size(),
                oldData.data(), oldData.data()+oldData.size(),
                diff, kMinSingleMatchScore_default, false, 1);

    std::vector<unsigned char> outNew(newData.size());
    hpatch_BOOL ok = patch(outNew.data(), outNew.data()+outNew.size(),
                           oldData.data(), oldData.data()+oldData.size(),
                           diff.data(), diff.data()+diff.size());

    if (!ok) {
        std::cerr << "patch failed" << std::endl;
        return 1;
    }
    if (outNew != newData) {
        std::cerr << "mismatch" << std::endl;
        return 1;
    }
    std::cout << "OK" << std::endl;
    return 0;
}
