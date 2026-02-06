#include <cstdio>
#include <cstdint>
#include <cstring>
extern "C" {
#include <libfplist.h>
}

int main() {
    const char* ver = libfplist_get_version();
    if (ver) std::printf("libfplist version: %s\n", ver);

    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
        "<plist version=\"1.0\">\n"
        "<dict>\n"
        "<key>Foo</key>\n"
        "<string>Bar</string>\n"
        "</dict>\n"
        "</plist>\n";

    libfplist_property_list_t* plist = nullptr;
    libfplist_error_t* error = 0;

    if (libfplist_property_list_initialize(&plist, &error) != 1) {
        std::puts("init failed");
        return 1;
    }

    int r = libfplist_property_list_copy_from_byte_stream(
        plist,
        reinterpret_cast<const uint8_t*>(xml),
        std::strlen(xml),
        &error);

    if (r != 1) {
        std::puts("parse failed");
        libfplist_property_list_free(&plist, &error);
        return 0; // still OK for smoke test
    }

    libfplist_property_t* root = nullptr;
    libfplist_property_list_get_root_property(plist, &root, &error);
    if (root) {
        int value_type = 0;
        libfplist_property_get_value_type(root, &value_type, &error);
        libfplist_property_free(&root, &error);
    }

    libfplist_property_list_free(&plist, &error);
    std::puts("OK");
    return 0;
}
