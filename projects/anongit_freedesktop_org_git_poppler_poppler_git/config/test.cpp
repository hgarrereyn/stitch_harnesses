#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <iostream>

int main() {
    const char pdf_data[] = "%PDF-1.4\n%%EOF\n"; // intentionally minimal/invalid but enough to exercise API
    poppler::document *doc = poppler::document::load_from_raw_data(pdf_data, sizeof(pdf_data) - 1);
    if (!doc) {
        std::cout << "Document not loaded (as expected for minimal data)\n";
        return 0;
    }
    int pages = doc->pages();
    std::cout << "Pages: " << pages << "\n";
    delete doc;
    return 0;
}
