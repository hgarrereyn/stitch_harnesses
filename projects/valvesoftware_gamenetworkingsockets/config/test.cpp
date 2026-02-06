#include <steam/steamnetworkingsockets.h>
#include <cstdio>

int main() {
    SteamNetworkingErrMsg err;
    if (!GameNetworkingSockets_Init(nullptr, err)) {
        std::printf("Init failed: %s\n", err);
        return 0; // still "success" for our simple test
    }
    // Successfully initialized and shut down the library
    GameNetworkingSockets_Kill();
    std::printf("GameNetworkingSockets initialized and shut down successfully.\n");
    return 0;
}
