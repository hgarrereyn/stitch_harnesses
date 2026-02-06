#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include <clib/clib-package.h>
}

int main() {
    const char *repo = "clibs/clib";
    char *name = clib_package_parse_name(repo);
    char *author = clib_package_parse_author(repo);
    if (name && author) {
        char *url = clib_package_url_from_repo(repo, "v1.0.0");
        printf("author=%s name=%s url=%s\n", author, name, url ? url : "(null)");
        free(name);
        free(author);
        if (url) free(url);
        return 0;
    }
    return 1;
}
