#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>

int main() {
    amqp_connection_state_t state = amqp_new_connection();
    amqp_socket_t *sock = amqp_tcp_socket_new(state);
    (void)sock; // we don't actually connect; just ensure symbols are available
    amqp_destroy_connection(state);
    return 0;
}
