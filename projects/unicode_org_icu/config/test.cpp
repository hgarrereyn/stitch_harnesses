#include <stdio.h>
#include <unicode/uversion.h>
#include <unicode/utypes.h>

int main() {
    UVersionInfo ver;
    u_getVersion(ver);
    char verStr[U_MAX_VERSION_STRING_LENGTH];
    u_versionToString(ver, verStr);
    printf("ICU version: %s\n", verStr);
    return 0;
}
