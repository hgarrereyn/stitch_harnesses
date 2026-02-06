#include <tesseract/capi.h>
#include <tesseract/baseapi.h>
#include <iostream>

int main() {
    const char* ver = TessVersion();
    std::cout << "Tesseract version: " << (ver ? ver : "(null)") << "\n";

    tesseract::TessBaseAPI api;
    api.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);

    std::cout << "API created and configured successfully." << std::endl;
    return 0;
}
