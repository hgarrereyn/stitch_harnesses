#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Identity.h"

int main() {
    // Exercise library: create random keys and compute identity hash abbreviation
    i2p::data::PrivateKeys keys = i2p::data::PrivateKeys::CreateRandomKeys(
        i2p::data::SIGNING_KEY_TYPE_ECDSA_SHA256_P256,
        i2p::data::CRYPTO_KEY_TYPE_ECIES_X25519_AEAD,
        true
    );
    auto pub = keys.GetPublic();
    auto hash = pub->GetIdentHash();
    std::string abbrev = i2p::data::GetIdentHashAbbreviation(hash);
    std::cout << "Created identity abbrev: " << abbrev << "\n";
    return 0;
}
