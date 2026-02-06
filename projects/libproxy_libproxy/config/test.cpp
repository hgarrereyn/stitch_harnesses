#include <stdio.h>
#include <libproxy/proxy.h>

int main() {
    pxProxyFactory *factory = px_proxy_factory_new();
    if (!factory) {
        printf("Failed to create pxProxyFactory\n");
        return 0;
    }
    const char *url = "http://www.example.com";
    char **proxies = px_proxy_factory_get_proxies(factory, url);
    if (proxies && proxies[0]) {
        printf("First proxy for %s: %s\n", url, proxies[0]);
    } else {
        printf("No proxy or direct connection for %s\n", url);
    }
    px_proxy_factory_free_proxies(proxies);
    px_proxy_factory_free(factory);
    return 0;
}
