#include <proton/message.h>
#include <proton/codec.h>
#include <stdio.h>
#include <string.h>

int main() {
    pn_message_t *msg = pn_message();
    if (!msg) { printf("pn_message() failed\n"); return 1; }
    pn_message_set_durable(msg, true);
    pn_message_set_subject(msg, "hello");

    // Put a simple string body
    pn_data_t *body = pn_message_body(msg);
    pn_data_clear(body);
    pn_data_put_string(body, pn_bytes(5, "world"));

    // Encode
    char buf[1024];
    size_t size = sizeof(buf);
    int rc = pn_message_encode(msg, buf, &size);
    if (rc) { printf("encode error %d\n", rc); pn_message_free(msg); return 1; }

    // Decode into a new message
    pn_message_t *msg2 = pn_message();
    size_t dsize = size;
    rc = pn_message_decode(msg2, buf, dsize);
    if (rc) { printf("decode error %d\n", rc); pn_message_free(msg); pn_message_free(msg2); return 1; }

    const char *subject = pn_message_get_subject(msg2);
    printf("subject=%s size=%zu\n", subject ? subject : "(null)", size);

    pn_message_free(msg);
    pn_message_free(msg2);
    return 0;
}
