#include <libspectre/spectre.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int main() {
    // Create a tiny PostScript file we can load
    const char *ps = "%!PS-Adobe-3.0\n"
                     "%%Pages: 1\n"
                     "%%BoundingBox: 0 0 100 100\n"
                     "%%EndComments\n"
                     "newpath 10 10 moveto 90 90 lineto stroke\n"
                     "showpage\n";
    std::string path = "/tmp/libspectre_test.ps";
    FILE *f = std::fopen(path.c_str(), "wb");
    if (!f) return 0;
    std::fwrite(ps, 1, std::strlen(ps), f);
    std::fclose(f);

    SpectreDocument *doc = spectre_document_new();
    spectre_document_load(doc, path.c_str());
    SpectreStatus st = spectre_document_status(doc);
    unsigned int pages = 0;
    if (st == SPECTRE_STATUS_SUCCESS) {
        pages = spectre_document_get_n_pages(doc);
    }

    // Basic sanity output
    std::printf("status=%d pages=%u\n", (int)st, pages);

    spectre_document_free(doc);
    return 0;
}
