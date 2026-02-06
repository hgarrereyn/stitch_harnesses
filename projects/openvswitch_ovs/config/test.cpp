#include <openvswitch/util.h>
#include <openvswitch/json.h>
#include <stdio.h>

int main() {
    ovs_set_program_name("ovstest", "1.0");

    struct json *obj = json_object_create();
    json_object_put_string(obj, "hello", "world");
    json_object_put_format(obj, "number", "%d", 42);

    char *s = json_to_string(obj, 0);
    printf("%s\n", s ? s : "(null)");

    free(s);
    json_destroy(obj);
    return 0;
}
