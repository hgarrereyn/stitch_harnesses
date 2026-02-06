#include <iostream>
#include <coap3/coap.h>

int main() {
  coap_startup();
  coap_context_t* ctx = coap_new_context(NULL);
  if (!ctx) {
    std::cout << "Failed to create libcoap context" << std::endl;
    coap_cleanup();
    return 0;
  }
  coap_context_set_keepalive(ctx, 0);
  coap_context_set_session_timeout(ctx, 10);
  coap_free_context(ctx);
  coap_cleanup();
  std::cout << "libcoap basic init/shutdown OK" << std::endl;
  return 0;
}
