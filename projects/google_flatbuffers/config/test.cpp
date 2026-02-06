#include <iostream>
#include <flatbuffers/flexbuffers.h>

int main() {
    // Build a simple FlexBuffer: {"answer": 42, "hello":"world"}
    flexbuffers::Builder fbb;
    fbb.Map([&](){
        fbb.Int("answer", 42);
        fbb.String("hello", "world");
    });
    fbb.Finish();

    auto buf = fbb.GetBuffer();
    auto root = flexbuffers::GetRoot(buf).AsMap();
    int answer = root["answer"].AsInt32();
    std::string hello = root["hello"].AsString().str();

    std::cout << "answer=" << answer << ", hello=" << hello << std::endl;
    if (answer != 42 || hello != "world") return 1;
    return 0;
}
