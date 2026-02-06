#include <stdio.h>
#include <stdlib.h>
#ifndef restrict
#define restrict
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include <bcl.h>
#ifdef __cplusplus
}
#endif

int main() {
    if (bcl_start() != BCL_ERROR_NONE) {
        fprintf(stderr, "bcl_start failed\n");
        return 1;
    }
    if (bcl_init() != BCL_ERROR_NONE) {
        fprintf(stderr, "bcl_init failed\n");
        bcl_end();
        return 1;
    }

    BclContext ctxt = bcl_ctxt_create();
    if (!ctxt) {
        fprintf(stderr, "bcl_ctxt_create failed\n");
        bcl_free();
        bcl_end();
        return 1;
    }
    if (bcl_pushContext(ctxt) != BCL_ERROR_NONE) {
        fprintf(stderr, "bcl_pushContext failed\n");
        bcl_ctxt_free(ctxt);
        bcl_free();
        bcl_end();
        return 1;
    }

    BclNumber a = bcl_bigdig2num(2);
    BclNumber b = bcl_bigdig2num(3);

    if (bcl_err(a) != BCL_ERROR_NONE || bcl_err(b) != BCL_ERROR_NONE) {
        fprintf(stderr, "failed to create numbers\n");
        bcl_popContext();
        bcl_ctxt_free(ctxt);
        bcl_free();
        bcl_end();
        return 1;
    }

    BclNumber c = bcl_add_keep(a, b);
    if (bcl_err(c) != BCL_ERROR_NONE) {
        fprintf(stderr, "add failed\n");
        bcl_num_free(a);
        bcl_num_free(b);
        bcl_popContext();
        bcl_ctxt_free(ctxt);
        bcl_free();
        bcl_end();
        return 1;
    }

    char* s = bcl_string_keep(c);
    if (!s) {
        fprintf(stderr, "string failed\n");
        bcl_num_free(a);
        bcl_num_free(b);
        bcl_num_free(c);
        bcl_popContext();
        bcl_ctxt_free(ctxt);
        bcl_free();
        bcl_end();
        return 1;
    }

    printf("2 + 3 = %s\n", s);

    free(s);
    bcl_num_free(a);
    bcl_num_free(b);
    bcl_num_free(c);

    bcl_popContext();
    bcl_ctxt_free(ctxt);
    bcl_free();
    bcl_end();
    return 0;
}
