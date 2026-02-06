#include <iostream>
#include <json.h>

int main() {
    const char *text = "{\"hello\":\"world\",\"number\":42}";
    json_value *val = json_parse(text, strlen(text));
    if (!val) {
        std::cout << "parse failed\n";
        return 0;
    }
    const json_value &obj = *val;
    if (obj.type == json_object) {
        const json_value &hello = obj["hello"];
        const json_value &number = obj["number"];
        std::cout << "hello=" << (const char*)hello << ", number=" << (double)number << "\n";
    }
    json_value_free(val);
    return 0;
}
