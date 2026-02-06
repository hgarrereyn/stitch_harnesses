#include <iostream>
extern "C" {
#include <archive.h>
#include <archive_entry.h>
}

int main() {
    struct archive *a = archive_write_new();
    if (!a) { std::cout << "archive_write_new failed\n"; return 0; }
    archive_write_set_format_raw(a);
    const size_t bufsize = 1024;
    char buffer[bufsize];
    size_t used = 0;
    if (archive_write_open_memory(a, buffer, bufsize, &used) != ARCHIVE_OK) {
        std::cout << "open_memory failed: " << archive_error_string(a) << "\n";
        archive_write_free(a);
        return 0;
    }
    struct archive_entry *entry = archive_entry_new();
    archive_entry_set_pathname(entry, "hello.txt");
    archive_entry_set_filetype(entry, AE_IFREG);
    const char *data = "hello";
    archive_entry_set_size(entry, 5);
    if (archive_write_header(a, entry) != ARCHIVE_OK) {
        std::cout << "write_header failed: " << archive_error_string(a) << "\n";
    } else {
        la_ssize_t w = archive_write_data(a, data, 5);
        std::cout << "wrote bytes: " << (long long)w << ", used buffer: " << (long long)used << "\n";
    }
    archive_entry_free(entry);
    archive_write_close(a);
    archive_write_free(a);
    std::cout << "OK\n";
    return 0;
}
