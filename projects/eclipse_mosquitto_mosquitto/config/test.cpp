#include <mosquitto.h>
#include <stdio.h>

static void on_connect(struct mosquitto*, void*, int){ }

int main(){
    if(mosquitto_lib_init() != MOSQ_ERR_SUCCESS){
        return 1;
    }

    struct mosquitto *m = mosquitto_new("test_client", true, NULL);
    if(m){
        mosquitto_connect_callback_set(m, on_connect);
        mosquitto_destroy(m);
    }

    mosquitto_lib_cleanup();
    printf("mosquitto library initialized and cleaned up.\n");
    return 0;
}
