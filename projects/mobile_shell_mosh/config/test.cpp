#include <iostream>
#include "src/crypto/crypto.h"

int main() {
  try {
    Crypto::Base64Key key; // random key
    Crypto::Session session(key);

    uint64_t n = Crypto::unique();
    Crypto::Nonce nonce(n);

    std::string plaintext = "hello mosh";
    Crypto::Message msg(nonce, plaintext);

    std::string ciphertext = session.encrypt(msg);
    Crypto::Message dec = session.decrypt(ciphertext);

    if (dec.text != plaintext) {
      std::cerr << "Roundtrip failed" << std::endl;
      return 1;
    }

    std::cout << "OK: " << dec.text << " (" << ciphertext.size() << " bytes encrypted)\n";
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 2;
  }
  return 0;
}
