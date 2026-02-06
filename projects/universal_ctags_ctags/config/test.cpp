#include <cstdio>
#include <cstdlib>
extern "C" {
#include <readtags.h>
}

int main() {
    const char* path = "/tmp/sample.tags";
    // Create a minimal tags file
    FILE* f = std::fopen(path, "w");
    if (!f) return 0;
    std::fputs("!_TAG_FILE_FORMAT\t2\t/extended format/\n", f);
    std::fputs("!_TAG_FILE_SORTED\t1\t/0=unsorted, 1=sorted, 2=foldcase/\n", f);
    std::fputs("main\tfile.c\t/^int main() {}/;\"\n", f);
    std::fclose(f);

    tagFileInfo info{};
    tagFile* tf = tagsOpen(path, &info);
    if (!tf || !info.status.opened) {
        return 0; // gracefully exit if open fails
    }

    tagEntry entry{};
    if (tagsFind(tf, &entry, "main", TAG_FULLMATCH) == TagSuccess) {
        // Found entry; exercise a couple of fields
        // printf("name=%s file=%s\n", entry.name, entry.file);
    }

    tagsClose(tf);
    return 0;
}
