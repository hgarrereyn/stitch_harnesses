#include <iostream>
#include "kcodecs.h"

int main() {
    QByteArray input("Aladdin:open sesame");
    QByteArray out = KCodecs::base64Encode(QByteArrayView(input));
    std::cout << out.constData() << "\n";
    return out.isEmpty() ? 1 : 0;
}
