#include <cstdio>
#include <libexif/exif-data.h>
#include <libexif/exif-tag.h>
#include <libexif/exif-content.h>

static void print_entry(ExifEntry *entry, void *user_data) {
    (void)user_data;
    char value[1024];
    exif_entry_get_value(entry, value, sizeof(value));
    if (value[0]) {
        printf("Tag %d: %s\n", entry->tag, value);
    }
}

static void print_ifd(ExifContent *content, void *user_data) {
    (void)user_data;
    exif_content_foreach_entry(content, print_entry, nullptr);
}

int main() {
    ExifData *d = exif_data_new();
    if (!d) {
        printf("Failed to create ExifData\n");
        return 0;
    }
    // Ensure it's in a consistent state
    exif_data_fix(d);
    // Iterate contents (will be empty but exercises API)
    exif_data_foreach_content(d, print_ifd, nullptr);
    // Dump for good measure
    exif_data_dump(d);
    exif_data_free(d);
    return 0;
}
