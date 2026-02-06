#include <iostream>
#include <cstring>
extern "C" {
#include <yyjson.h>
}

int main() {
    const char *json = "{\"name\":\"Mash\",\"star\":4,\"hits\":[2,2,1,3]}";
    yyjson_doc *doc = yyjson_read(json, strlen(json), 0);
    if (!doc) {
        std::cout << "Failed to parse JSON\n";
        return 1;
    }
    yyjson_val *root = yyjson_doc_get_root(doc);
    yyjson_val *name = yyjson_obj_get(root, "name");
    yyjson_val *star = yyjson_obj_get(root, "star");
    if (name && star) {
        std::cout << "name: " << yyjson_get_str(name) << ", star: " << (long long)yyjson_get_int(star) << "\n";
    }
    // Write a small JSON using mutable API
    yyjson_mut_doc *mdoc = yyjson_mut_doc_new(NULL);
    yyjson_mut_val *mroot = yyjson_mut_obj(mdoc);
    yyjson_mut_doc_set_root(mdoc, mroot);
    yyjson_mut_obj_add_str(mdoc, mroot, "hello", "world");
    const char *out = yyjson_mut_write(mdoc, 0, NULL);
    if (out) {
        std::cout << out << "\n";
        free((void*)out);
    }
    yyjson_doc_free(doc);
    yyjson_mut_doc_free(mdoc);
    return 0;
}
