#include <stdio.h>
#include <dovecot/config.h>
#include <dovecot/lib.h>
#include <dovecot/str.h>

int main() {
    // Just verify headers are usable and print version macro
    printf("Dovecot version: %s\n", DOVECOT_VERSION);
    // Create and use a type from the headers without calling into the library
    (void)sizeof(string_t*); // ensure type is visible
    return 0;
}
