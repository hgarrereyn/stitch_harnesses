#include <iostream>
#include <cstring>
#include <cld2/public/compact_lang_det.h>
#include <cld2/public/encodings.h>

int main() {
    const char* text = "Hello world. This is a language detection test.";
    bool reliable = false;
    CLD2::Language lang = CLD2::DetectLanguage(text, (int)std::strlen(text), true, &reliable);
    std::cout << "Detected language enum: " << (int)lang << ", reliable=" << (reliable ? "true" : "false") << std::endl;
    return 0;
}
