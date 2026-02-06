#include <cstdio>
#include <cstring>
extern "C" {
#include <wolfmqtt/mqtt_client.h>
}

static int msg_cb(MqttClient* /*client*/, MqttMessage* /*msg*/, unsigned char /*msg_new*/, unsigned char /*msg_done*/)
{
    return 0; // no-op
}

int main() {
    MqttNet net; std::memset(&net, 0, sizeof(net));
    unsigned char tx_buf[512];
    unsigned char rx_buf[512];

    MqttClient client; std::memset(&client, 0, sizeof(client));
    int rc = MqttClient_Init(&client, &net, msg_cb, tx_buf, sizeof(tx_buf), rx_buf, sizeof(rx_buf), 1000);
    std::printf("MqttClient_Init rc=%d\n", rc);

    const char* ver = MqttClient_GetProtocolVersionString(&client);
    if (ver) std::printf("wolfMQTT protocol default: %s\n", ver);

    MqttClient_DeInit(&client);
    return 0;
}
