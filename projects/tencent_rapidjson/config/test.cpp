#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <cstdio>

int main() {
    // Create a JSON object and stringify it
    rapidjson::Document d;
    d.SetObject();
    auto& alloc = d.GetAllocator();
    d.AddMember(rapidjson::Value("hello", alloc), rapidjson::Value("world", alloc), alloc);
    d.AddMember("answer", 42, alloc);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    const char* json = buffer.GetString();
    // Parse it back
    rapidjson::Document d2;
    d2.Parse(json);
    if (d2.HasParseError() || !d2.IsObject()) return 1;
    if (!d2.HasMember("hello") || !d2["hello"].IsString()) return 2;
    if (std::string(d2["hello"].GetString()) != "world") return 3;
    if (!d2.HasMember("answer") || !d2["answer"].IsInt()) return 4;

    std::printf("%s\n", json);
    return 0;
}
