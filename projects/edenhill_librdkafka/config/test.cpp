#include <stdio.h>
#include <librdkafka/rdkafka.h>

int main() {
    const char *verstr = rd_kafka_version_str();
    printf("librdkafka version: %s\n", verstr);

    char errstr[512];
    rd_kafka_conf_t *conf = rd_kafka_conf_new();

    if (rd_kafka_conf_set(conf, "bootstrap.servers", "localhost:9092", errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
        fprintf(stderr, "conf_set failed: %s\n", errstr);
        return 1;
    }

    rd_kafka_t *rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
    if (!rk) {
        fprintf(stderr, "rd_kafka_new failed: %s\n", errstr);
        return 1;
    }

    // Immediately destroy to avoid any network interaction.
    rd_kafka_destroy(rk);
    printf("Created and destroyed producer successfully.\n");
    return 0;
}
