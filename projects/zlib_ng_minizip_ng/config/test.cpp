#include <cstdio>
#include <cstring>
#include <string>

extern "C" {
#include <mz.h>
#include <mz_strm.h>
#include <mz_zip.h>
#include <mz_zip_rw.h>
}

int main() {
    const char *zip_path = "/tmp/minizip_ng_test.zip";

    // Create a simple archive with one entry
    void *writer = mz_zip_writer_create();
    if (!writer) return 1;
    if (mz_zip_writer_open_file(writer, zip_path, 0, 0) != MZ_OK) {
        mz_zip_writer_delete(&writer);
        return 2;
    }

    const char *data = "hello minizip-ng";
    mz_zip_file file_info; std::memset(&file_info, 0, sizeof(file_info));
    file_info.filename = "greeting.txt";
    file_info.compression_method = MZ_COMPRESS_METHOD_DEFLATE;

    if (mz_zip_writer_add_buffer(writer, data, (int32_t)std::strlen(data), &file_info) != MZ_OK) {
        mz_zip_writer_close(writer);
        mz_zip_writer_delete(&writer);
        return 3;
    }

    if (mz_zip_writer_close(writer) != MZ_OK) {
        mz_zip_writer_delete(&writer);
        return 4;
    }
    mz_zip_writer_delete(&writer);

    // Read back the archive and count entries
    void *reader = mz_zip_reader_create();
    if (!reader) return 5;
    if (mz_zip_reader_open_file(reader, zip_path) != MZ_OK) {
        mz_zip_reader_delete(&reader);
        return 6;
    }

    int count = 0;
    if (mz_zip_reader_goto_first_entry(reader) == MZ_OK) {
        do { count++; } while (mz_zip_reader_goto_next_entry(reader) == MZ_OK);
    }

    mz_zip_reader_close(reader);
    mz_zip_reader_delete(&reader);

    std::printf("Created and read zip with %d entries\n", count);
    return count == 1 ? 0 : 7;
}
