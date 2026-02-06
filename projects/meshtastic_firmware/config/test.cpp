#include <iostream>
#include "serialization/JSON.h"

int main() {
    const char* text = "{\"msg\":\"hello\",\"ok\":true,\"n\":123}";
    JSONValue* root = JSON::Parse(text);
    if (!root) {
        std::cout << "Parse failed\n";
        return 0;
    }
    // Access a couple of fields
    if (root->IsObject()) {
        auto obj = root->AsObject();
        if (obj.count("msg")) {
            std::cout << "msg: " << obj["msg"]->AsString() << "\n";
        }
        if (obj.count("ok")) {
            std::cout << "ok: " << (obj["ok"]->AsBool() ? "true" : "false") << "\n";
        }
        std::cout << "stringified: " << root->Stringify(true) << "\n";
    }
    delete root;
    return 0;
}
