#include <fastdfs/fdfs_client.h>
#include <cstdio>
#include <cstring>

int main() {
    // Use some simple API that doesn't require servers
    const char *ext = fdfs_get_file_ext_name_ex("example.tar.gz", true);
    if (ext) {
        printf("ext=%s\n", ext);
    } else {
        printf("no ext\n");
    }

    char file_id[256];
    fdfs_combine_file_id("group1", "M00/00/00/abcdef", file_id);
    printf("file_id=%s\n", file_id);

    TrackerServerGroup g1; memset(&g1, 0, sizeof(g1));
    TrackerServerGroup g2; memset(&g2, 0, sizeof(g2));
    bool eq = fdfs_tracker_group_equals(&g1, &g2);
    printf("groups_equal=%s\n", eq ? "true" : "false");

    return 0;
}
