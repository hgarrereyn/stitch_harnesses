#include <zip.h>
#include <cstdio>
#include <cstring>
#include <string>

int main() {
    int errorp = 0;
    const char *zip_path = "/tmp/libzip_test.zip";

    // Create a new zip archive
    zip_t *za = zip_open(zip_path, ZIP_TRUNCATE | ZIP_CREATE, &errorp);
    if (!za) {
        fprintf(stderr, "Failed to create zip: error=%d\n", errorp);
        return 1;
    }

    const char *filename_in_zip = "hello.txt";
    const char *content = "Hello from libzip!\n";
    zip_source_t *src = zip_source_buffer(za, content, strlen(content), 0);
    if (!src) {
        fprintf(stderr, "zip_source_buffer failed: %s\n", zip_strerror(za));
        zip_discard(za);
        return 1;
    }

    zip_int64_t idx = zip_file_add(za, filename_in_zip, src, ZIP_FL_OVERWRITE);
    if (idx < 0) {
        fprintf(stderr, "zip_file_add failed: %s\n", zip_strerror(za));
        zip_source_free(src);
        zip_discard(za);
        return 1;
    }

    if (zip_close(za) != 0) {
        fprintf(stderr, "zip_close failed\n");
        return 1;
    }

    // Re-open and read back the file
    za = zip_open(zip_path, 0, &errorp);
    if (!za) {
        fprintf(stderr, "Failed to reopen zip: error=%d\n", errorp);
        return 1;
    }

    struct zip_stat st; 
    zip_stat_init(&st);
    if (zip_stat(za, filename_in_zip, 0, &st) != 0) {
        fprintf(stderr, "zip_stat failed: %s\n", zip_strerror(za));
        zip_discard(za);
        return 1;
    }

    zip_file_t *zf = zip_fopen(za, filename_in_zip, 0);
    if (!zf) {
        fprintf(stderr, "zip_fopen failed: %s\n", zip_strerror(za));
        zip_discard(za);
        return 1;
    }

    std::string buf;
    buf.resize(st.size);
    zip_int64_t n = zip_fread(zf, buf.data(), buf.size());
    zip_fclose(zf);
    zip_discard(za);

    if (n < 0) {
        fprintf(stderr, "zip_fread failed\n");
        return 1;
    }

    // Print read content size to verify
    printf("Read %lld bytes: %.*s", (long long)n, (int)n, buf.c_str());
    return 0;
}
