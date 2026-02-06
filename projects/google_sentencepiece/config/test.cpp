#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sentencepiece_trainer.h>
#include <sentencepiece_processor.h>

int main() {
    using namespace sentencepiece;
    // Tiny training corpus
    std::vector<std::string> corpus = {
        "hello world",
        "hello fuzzing",
        "sentence piece",
        "tokenization test"
    };

    std::string model_proto;
    auto status = SentencePieceTrainer::Train(
        std::unordered_map<std::string, std::string>{
            {"model_type", "unigram"},
            {"vocab_size", "24"},
            {"character_coverage", "1.0"}
        },
        corpus,
        &model_proto
    );
    if (!status.ok()) {
        std::cerr << "Training failed: " << status.ToString() << std::endl;
        return 1;
    }

    SentencePieceProcessor sp;
    status = sp.LoadFromSerializedProto(model_proto);
    if (!status.ok()) {
        std::cerr << "LoadFromSerializedProto failed: " << status.ToString() << std::endl;
        return 1;
    }

    std::string input = "hello world";
    std::vector<std::string> pieces;
    status = sp.Encode(input, &pieces);
    if (!status.ok()) {
        std::cerr << "Encode failed: " << status.ToString() << std::endl;
        return 1;
    }

    std::string detok;
    status = sp.Decode(pieces, &detok);
    if (!status.ok()) {
        std::cerr << "Decode failed: " << status.ToString() << std::endl;
        return 1;
    }

    std::cout << "Encoded pieces: ";
    for (const auto &p : pieces) std::cout << p << ' ';
    std::cout << "\nDetok: " << detok << std::endl;
    return 0;
}
