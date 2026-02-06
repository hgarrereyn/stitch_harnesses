#include <iostream>
#include <string>
extern "C" {
#include <json-c/json.h>
}

int main() {
    json_object *obj = json_object_new_object();
    json_object_object_add(obj, "hello", json_object_new_string("world"));
    json_object_object_add(obj, "answer", json_object_new_int(42));

    const char *s = json_object_to_json_string_ext(obj, JSON_C_TO_STRING_SPACED);
    std::cout << "Serialized: " << s << std::endl;

    json_object *parsed = json_tokener_parse(s);
    if (!parsed) {
        std::cerr << "Parse failed" << std::endl;
        json_object_put(obj);
        return 1;
    }

    json_object *answer = nullptr;
    if (json_object_object_get_ex(parsed, "answer", &answer)) {
        std::cout << "Answer: " << json_object_get_int(answer) << std::endl;
    }

    json_object_put(parsed);
    json_object_put(obj);
    return 0;
}
