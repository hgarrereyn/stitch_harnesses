#include <iostream>
#include <string>
#include <vector>
#include <sentencepiece_processor.h>

int main() {
    sentencepiece::SentencePieceProcessor sp;
    // Try to load an empty/invalid model to exercise the API without external data
    sentencepiece::util::Status status = sp.LoadFromSerializedProto("");
    std::cout << "LoadFromSerializedProto ok: " << (status.ok() ? "true" : "false") << "\n";

    std::cout << "Program finished" << std::endl;
    return 0;
}
