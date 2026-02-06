#include <enet/enet.h>
#include <cstdio>

int main() {
    if (enet_initialize() != 0) {
        std::printf("ENet initialization failed\n");
        return 1;
    }

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 0; // any available port

    ENetHost* server = enet_host_create(&address, /*max peers*/ 1, /*channels*/ 2,
                                        /*in bandwidth*/ 0, /*out bandwidth*/ 0);
    if (!server) {
        std::printf("Failed to create ENet host\n");
        enet_deinitialize();
        return 1;
    }

    ENetEvent event;
    // Non-blocking service; should immediately return 0 events
    enet_host_service(server, &event, 0);

    const char* msg = "hi";
    ENetPacket* packet = enet_packet_create(msg, 2, ENET_PACKET_FLAG_RELIABLE);
    if (packet) {
        // Normally we'd send to a peer; here we just destroy it to exercise API
        enet_packet_destroy(packet);
    }

    enet_host_destroy(server);
    enet_deinitialize();
    std::printf("ENet basic test completed.\n");
    return 0;
}
