#include <stdio.h>
#include <string.h>
#include <jq.h>
#include <jv.h>

int main() {
    jq_state *jq = jq_init();
    if (!jq) {
        fprintf(stderr, "jq_init failed\n");
        return 1;
    }

    const char *program = "."; // identity filter
    if (!jq_compile(jq, program)) {
        fprintf(stderr, "jq_compile failed\n");
        jq_teardown(&jq);
        return 1;
    }

    jv input = jv_parse("{\"hello\": \"world\"}");
    if (!jv_is_valid(jv_copy(input))) {
        fprintf(stderr, "invalid input JSON\n");
        jq_teardown(&jq);
        return 1;
    }

    jq_start(jq, jv_copy(input), 0);

    jv out = jq_next(jq);
    if (jv_is_valid(jv_copy(out))) {
        // Print the output to stdout
        jv_dump(out, JV_PRINT_PRETTY);
        putchar('\n');
        jv_free(out);
    } else {
        jv msg = jv_invalid_get_msg(out);
        fprintf(stderr, "jq execution error: ");
        jv_dump(msg, 0);
        putchar('\n');
    }

    jv_free(input);
    jq_teardown(&jq);
    return 0;
}
