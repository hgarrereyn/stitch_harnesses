#include <cstdio>
#include <sepol/sepol.h>

int main() {
    // Create a temporary empty file and attempt to set policydb from it.
    const char *path = "/tmp/empty.policy";
    FILE *fp = fopen(path, "wb+");
    if (!fp) {
        printf("Failed to open temp file\n");
        return 0;
    }
    // no content written
    fflush(fp);
    rewind(fp);
    int rc = sepol_set_policydb_from_file(fp);
    printf("sepol_set_policydb_from_file returned %d\n", rc);
    fclose(fp);
    return 0;
}
