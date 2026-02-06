#include <cstdio>
extern "C" {
#include "/fuzz/install/include/rsync/lib/wildmatch.h"
}

int main() {
    const char* pattern = "*.txt";
    const char* fname1 = "readme.txt";
    const char* fname2 = "image.png";
    int m1 = wildmatch(pattern, fname1);
    int m2 = wildmatch(pattern, fname2);
    // Expect non-zero for match, zero for no match
    printf("%d %d\n", m1 != 0, m2 == 0);
    return 0;
}
