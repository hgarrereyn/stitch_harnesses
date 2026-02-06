#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <toaru/hashmap.h>
#include <toaru/list.h>
#include <toaru/json.h>

int main() {
    // Test hashmap and list
    hashmap_t *map = hashmap_create(10);
    hashmap_set(map, "hello", strdup("world"));
    hashmap_set(map, "number", strdup("42"));

    list_t *keys = hashmap_keys(map);
    size_t count = 0;
    for (node_t *n = keys->head; n; n = n->next) count++;

    printf("keys=%zu value=%s\n", count, (char*)hashmap_get(map, "hello"));

    // Test JSON parse
    const char *json = "{\"a\":123,\"b\":[true,false,\"x\"]}";
    struct JSON_Value *v = json_parse(json);
    if (!v) {
        printf("json parse failed\n");
    } else {
        struct JSON_Value *a = JSON_KEY(v, "a");
        if (a && a->type == JSON_TYPE_NUMBER) {
            printf("a=%d\n", (int)a->number);
        }
    }

    // cleanup basic structures we created
    // free keys list container only
    list_free(keys); free(keys);
    // free values in map
    list_t *vals = hashmap_values(map);
    for (node_t *n = vals->head; n; n = n->next) free(n->value);
    list_free(vals); free(vals);
    hashmap_free(map); free(map);

    if (v) json_free(v);

    return 0;
}
