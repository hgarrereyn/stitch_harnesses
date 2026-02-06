#include <iostream>
#include <esl/esl.h>
#include <esl/esl_event.h>

int main() {
    esl_event_t *e = nullptr;
    if (esl_event_create(&e, ESL_EVENT_CHANNEL_CREATE) != ESL_SUCCESS || !e) {
        std::cout << "Failed to create event\n";
        return 1;
    }
    esl_event_add_header(e, ESL_STACK_TOP, "Test-Header", "HelloWorld");
    const char *val = esl_event_get_header(e, "Test-Header");
    std::cout << (val ? val : "<null>") << "\n";
    char *serialized = nullptr;
    esl_event_serialize(e, &serialized, ESL_TRUE);
    if (serialized) {
        std::cout << "Serialized length: " << strlen(serialized) << "\n";
        free(serialized);
    }
    esl_event_destroy(&e);
    return 0;
}
