#include <stdio.h>
#include <string.h>
#include "jsmn.h"

int main() {
    const char *json = "{\"k\":123, \"ok\":true}";
    jsmn_parser p; jsmn_init(&p);
    jsmntok_t tokens[8];
    int r = jsmn_parse(&p, json, (size_t)strlen(json), tokens, 8);
    printf("Parsed tokens: %d\n", r);
    return r >= 0 ? 0 : 1;
}
