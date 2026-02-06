#include <iostream>
#include <libpostal/libpostal.h>

int main() {
    // Use functions that do not require model/data setup
    const char *input = "The Book Club 100-106 Leonard St, London";
    // Choose lightweight normalization options that don't require transliteration/numex
    uint64_t opts = LIBPOSTAL_NORMALIZE_STRING_LOWERCASE | LIBPOSTAL_NORMALIZE_STRING_TRIM | LIBPOSTAL_NORMALIZE_STRING_REPLACE_HYPHENS | LIBPOSTAL_NORMALIZE_STRING_COMPOSE;
    char *out = libpostal_normalize_string(const_cast<char*>(input), opts);
    if (!out) {
        std::cout << "normalize failed\n";
        return 1;
    }

    // Tokenize as well
    size_t n = 0;
    libpostal_token_t *tokens = libpostal_tokenize(out, false, &n);

    std::cout << "Normalized: " << out << "\n";
    std::cout << "Tokens (" << n << "):" << "\n";
    for (size_t i = 0; i < n; i++) {
        std::string tok(out + tokens[i].offset, tokens[i].len);
        std::cout << i << ": type=" << tokens[i].type << ", '" << tok << "'\n";
    }

    free(out);
    free(tokens);
    return 0;
}
