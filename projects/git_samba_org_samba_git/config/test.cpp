#include <stdio.h>
#include <string.h>
#include <popt.h>

int main() {
    int verbose = 0;
    const char *name = NULL;

    struct poptOption optionsTable[] = {
        {"verbose", 'v', 0, &verbose, 0, "enable verbose output", NULL},
        {"name", 'n', POPT_ARG_STRING, &name, 0, "set name", "NAME"},
        POPT_TABLEEND
    };

    const char *argv_fake[] = {"prog", "--verbose", "--name", "samba", NULL};
    int argc_fake = 4;

    poptContext ctx = poptGetContext("prog", argc_fake, argv_fake, optionsTable, 0);
    if (!ctx) { printf("poptGetContext failed\n"); return 1; }

    int rc;
    while ((rc = poptGetNextOpt(ctx)) >= 0) {
        // iterate options
    }

    if (rc < -1) {
        printf("Error parsing options: %s\n", poptStrerror(rc));
        poptFreeContext(ctx);
        return 1;
    }

    printf("verbose=%d, name=%s\n", verbose, name ? name : "(null)");

    poptFreeContext(ctx);
    return 0;
}
