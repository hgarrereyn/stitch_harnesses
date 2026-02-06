extern "C" {
#include <samtools/sam_opts.h>
}
#include <stdio.h>

int main() {
    sam_global_args ga; // Will be set up by the init function
    sam_global_args_init(&ga);
    // Set a couple of fields to exercise the API
    ga.nthreads = 1;
    ga.write_index = 0;
    sam_global_args_free(&ga);
    puts("samtools libst test OK");
    return 0;
}
