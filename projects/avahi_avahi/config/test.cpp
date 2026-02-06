#include <cstdio>
#include <avahi-client/client.h>
#include <avahi-common/simple-watch.h>

int main() {
    int error = 0;
    AvahiSimplePoll* sp = avahi_simple_poll_new();
    if (!sp) {
        std::printf("Failed to create simple poll\n");
        return 0;
    }

    AvahiClient* client = avahi_client_new(avahi_simple_poll_get(sp), AVAHI_CLIENT_NO_FAIL, nullptr, nullptr, &error);
    if (!client) {
        std::printf("Failed to create AvahiClient (err=%d)\n", error);
    } else {
        const char* ver = avahi_client_get_version_string(client);
        int state = (int)avahi_client_get_state(client);
        std::printf("AvahiClient created. state=%d version=%s\n", state, ver ? ver : "<unknown>");
        avahi_client_free(client);
    }

    avahi_simple_poll_free(sp);
    return 0;
}
