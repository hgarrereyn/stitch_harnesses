#include <cstdio>
#include <cstring>
extern "C" {
#include "common.h"
#include "dos2unix.h"
}

int main() {
    const char *input = "Hello\r\nWorld\r\n";
    FILE *inF = tmpfile();
    FILE *outF = tmpfile();
    if (!inF || !outF) return 1;
    fwrite(input, 1, strlen(input), inF);
    fflush(inF);
    rewind(inF);

    CFlag flag{};
    flag.verbose = 0;
    flag.FromToMode = FROMTO_DOS2UNIX;

    int ret = ConvertDosToUnix(inF, outF, &flag, "test");
    if (ret != 0) return 1;
    fflush(outF);
    rewind(outF);

    char buf[64]{};
    size_t n = fread(buf, 1, sizeof(buf)-1, outF);
    buf[n] = '\0';

    if (strstr(buf, "\r") != nullptr) return 2;
    printf("%s", buf);
    return 0;
}
