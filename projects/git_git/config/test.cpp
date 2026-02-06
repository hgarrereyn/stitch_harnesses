#include <stdio.h>
extern "C" {
#include "version.h"
}

int main() {
    printf("Git version string: %s\n", git_version_string);
    printf("User agent: %s\n", git_user_agent());
    return 0;
}
