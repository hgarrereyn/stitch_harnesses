#include <iostream>
#include "dxflib/dl_writer_ascii.h"

int main() {
    // Use the API type without invoking any non-inline methods
    DL_WriterA* writerPtr = nullptr;
    std::cout << "dxflib header included, pointer=" << writerPtr << std::endl;
    return 0;
}
