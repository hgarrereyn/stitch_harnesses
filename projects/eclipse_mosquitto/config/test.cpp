#include <mosquitto.h>
#include <cstdio>

int main(){
    int major=0, minor=0, rev=0;
    mosquitto_lib_version(&major, &minor, &rev);
    if(mosquitto_lib_init()!=0){
        return 1;
    }
    struct mosquitto *m = mosquitto_new("test-client", true, nullptr);
    if(m){
        // Call a few simple library routines without network activity
        mosquitto_reconnect_delay_set(m, 1, 3, true);
        mosquitto_max_inflight_messages_set(m, 10);
        mosquitto_message_retry_set(m, 5);
        mosquitto_destroy(m);
    }
    mosquitto_lib_cleanup();
    std::printf("libmosquitto version: %d.%d.%d\n", major, minor, rev);
    return 0;
}