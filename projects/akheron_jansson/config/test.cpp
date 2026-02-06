#include <iostream>
extern "C" {
#include <jansson.h>
}

int main() {
    json_t* root = json_object();
    if(!root) return 1;
    json_object_set_new(root, "message", json_string("hello jansson"));
    json_t* arr = json_array();
    json_array_append_new(arr, json_integer(1));
    json_array_append_new(arr, json_integer(2));
    json_array_append_new(arr, json_integer(3));
    json_object_set_new(root, "numbers", arr);

    char* dumped = json_dumps(root, JSON_INDENT(2));
    if(dumped) {
        std::cout << dumped << std::endl;
        free(dumped);
    }

    json_decref(root);
    return 0;
}
