#include <json/json.h>
#include <iostream>
#include <sstream>

int main() {
    const std::string input = R"({"name":"World","answer":42,"arr":[1,2,3]})";

    Json::CharReaderBuilder rb;
    rb["collectComments"] = false;
    std::unique_ptr<Json::CharReader> reader(rb.newCharReader());

    Json::Value root;
    std::string errs;
    bool ok = reader->parse(input.data(), input.data() + input.size(), &root, &errs);
    if (!ok) {
        std::cerr << "Parse failed: " << errs << std::endl;
        return 1;
    }

    // Access some fields using APIs that avoid string_view overloads
    const Json::Value* vname = root.find(std::string("name"));
    std::string name = vname ? vname->asString() : std::string();
    const Json::Value* vans = root.find(std::string("answer"));
    int answer = vans ? vans->asInt() : 0;

    root[Json::StaticString("greeting")] = std::string("Hello ") + name;
    root[Json::StaticString("answer")] = answer + 1;

    Json::StreamWriterBuilder wb;
    wb["indentation"] = ""; // compact
    std::unique_ptr<Json::StreamWriter> writer(wb.newStreamWriter());
    std::ostringstream oss;
    writer->write(root, &oss);

    std::cout << oss.str() << std::endl;
    return 0;
}
