#include <stdio.h>
#include <xmlsec/xmlsec.h>
#include <xmlsec/crypto.h>
#include <xmlsec/dl.h>
#include <xmlsec/openssl/crypto.h>

int main() {
    if(xmlSecInit() < 0) {
        fprintf(stderr, "xmlSecInit failed\n");
        return 1;
    }

    if(xmlSecCheckVersion() == 0) {
        fprintf(stderr, "xmlsec library version mismatch\n");
        return 2;
    }

    /* Initialize dynamic loader and load OpenSSL backend */
    if(xmlSecCryptoDLInit() < 0) {
        fprintf(stderr, "xmlSecCryptoDLInit failed\n");
        return 3;
    }
    if(xmlSecCryptoDLLoadLibrary(BAD_CAST "openssl") < 0) {
        fprintf(stderr, "xmlSecCryptoDLLoadLibrary(openssl) failed\n");
        return 4;
    }
    if(xmlSecCryptoDLSetFunctions(xmlSecCryptoGetFunctions_openssl()) < 0) {
        fprintf(stderr, "xmlSecCryptoDLSetFunctions failed\n");
        return 5;
    }

    if(xmlSecCryptoAppInit(NULL) < 0) {
        fprintf(stderr, "xmlSecCryptoAppInit failed\n");
        return 6;
    }

    if(xmlSecCryptoInit() < 0) {
        fprintf(stderr, "xmlSecCryptoInit failed\n");
        return 7;
    }

    xmlSecCryptoShutdown();
    xmlSecCryptoAppShutdown();
    xmlSecCryptoDLShutdown();
    xmlSecShutdown();

    printf("xmlsec initialized with OpenSSL and shutdown successfully\n");
    return 0;
}
