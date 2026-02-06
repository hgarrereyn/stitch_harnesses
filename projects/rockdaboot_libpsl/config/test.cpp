#include <iostream>
#include <libpsl.h>

int main() {
    const psl_ctx_t *psl = psl_builtin();
    if (!psl) {
        std::cout << "Failed to load built-in PSL" << std::endl;
        return 1;
    }
    const char *domain = "www.example.com";
    int is_public = psl_is_public_suffix(psl, domain);
    const char *cookie_domain = ".com";
    int acceptable = psl_is_cookie_domain_acceptable(psl, domain, cookie_domain);
    const char *registrable = psl_registrable_domain(psl, domain);

    std::cout << domain << (is_public ? " is" : " is not") << " a public suffix" << std::endl;
    std::cout << "Cookie domain '" << cookie_domain << "' "
              << (acceptable ? "is" : "is not") << " acceptable" << std::endl;
    if (registrable) {
        std::cout << "Registrable domain: " << registrable << std::endl;
    }
    return 0;
}
