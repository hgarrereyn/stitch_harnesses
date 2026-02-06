#include <iostream>
#include <string>
#include <vector>
#include "easywsclient.hpp"

int main() {
    using easywsclient::WebSocket;
    WebSocket::pointer ws = WebSocket::create_dummy();
    if (!ws) {
        std::cerr << "Failed to create dummy websocket" << std::endl;
        return 1;
    }

    // Exercise a bit of the API (no-ops on dummy):
    ws->poll(0);
    ws->send("hello");
    ws->sendBinary(std::string("bin"));
    std::vector<uint8_t> bytes = {1,2,3,4};
    ws->sendBinary(bytes);
    ws->sendPing();

    bool dispatched = false;
    ws->dispatch([&](const std::string &msg){
        dispatched = true;
        std::cout << "Got message: " << msg << std::endl;
    });
    ws->dispatchBinary([&](const std::vector<uint8_t>& msg){
        dispatched = true;
        std::cout << "Got bin message of size: " << msg.size() << std::endl;
    });

    ws->close();
    auto state = ws->getReadyState();
    std::cout << "ReadyState: " << state << " Dispatched: " << dispatched << std::endl;

    delete ws;
    return 0;
}
