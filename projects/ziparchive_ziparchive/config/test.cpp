#include <cstdio>
#include <cstring>
#include <string>

extern "C" {
#include <mz.h>
#include <mz_zip.h>
#include <mz_strm_mem.h>
}

int main() {
    const char *text = "Hello, ZipArchive!";
    int32_t text_len = (int32_t)strlen(text);

    void *mem_stream = mz_stream_mem_create();
    if (!mem_stream) { printf("mem stream create failed\n"); return 1; }
    if (mz_stream_mem_open(mem_stream, NULL, MZ_OPEN_MODE_CREATE | MZ_OPEN_MODE_READWRITE) != MZ_OK) {
        printf("mem stream open failed\n");
        return 1;
    }

    void *zip = mz_zip_create();
    if (!zip) { printf("zip create failed\n"); return 1; }
    if (mz_zip_open(zip, mem_stream, MZ_OPEN_MODE_WRITE) != MZ_OK) {
        printf("zip open for write failed\n");
        return 1;
    }

    mz_zip_file file_info; memset(&file_info, 0, sizeof(file_info));
    file_info.filename = (const char*)"hello.txt";
    file_info.compression_method = MZ_COMPRESS_METHOD_DEFLATE;

    if (mz_zip_entry_write_open(zip, &file_info, MZ_COMPRESS_LEVEL_DEFAULT, 0, NULL) != MZ_OK) {
        printf("entry write open failed\n");
        return 1;
    }
    if (mz_zip_entry_write(zip, text, text_len) != text_len) {
        printf("entry write failed\n");
        return 1;
    }
    if (mz_zip_entry_close(zip) != MZ_OK) {
        printf("entry close failed\n");
        return 1;
    }
    if (mz_zip_close(zip) != MZ_OK) {
        printf("zip close failed\n");
        return 1;
    }

    // Fetch buffer
    const void *buf = nullptr; int32_t buflen = 0;
    mz_stream_mem_get_buffer(mem_stream, &buf);
    mz_stream_mem_get_buffer_length(mem_stream, &buflen);

    // Now read back from memory
    void *mem_stream_in = mz_stream_mem_create();
    mz_stream_mem_set_buffer(mem_stream_in, (void*)buf, buflen);
    if (mz_stream_mem_open(mem_stream_in, NULL, MZ_OPEN_MODE_READ) != MZ_OK) {
        printf("mem stream open read failed\n");
        return 1;
    }

    void *zip_in = mz_zip_create();
    if (mz_zip_open(zip_in, mem_stream_in, MZ_OPEN_MODE_READ) != MZ_OK) {
        printf("zip open read failed\n");
        return 1;
    }

    if (mz_zip_goto_first_entry(zip_in) != MZ_OK) {
        printf("goto first entry failed\n");
        return 1;
    }
    if (mz_zip_entry_read_open(zip_in, 0, NULL) != MZ_OK) {
        printf("entry read open failed\n");
        return 1;
    }
    char out[64]; memset(out, 0, sizeof(out));
    int32_t n = mz_zip_entry_read(zip_in, out, sizeof(out)-1);
    mz_zip_entry_close(zip_in);
    mz_zip_close(zip_in);

    // Cleanup
    mz_zip_delete(&zip);
    mz_zip_delete(&zip_in);
    mz_stream_mem_close(mem_stream);
    mz_stream_mem_close(mem_stream_in);
    mz_stream_mem_delete(&mem_stream);
    mz_stream_mem_delete(&mem_stream_in);

    printf("Read back %d bytes: %s\n", n, out);
    return 0;
}
