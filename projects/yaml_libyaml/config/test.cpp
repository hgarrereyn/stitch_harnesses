#include <iostream>
#include <string>
#include <yaml.h>

int main() {
    std::cout << "libyaml version: " << yaml_get_version_string() << "\n";

    const unsigned char yaml_text[] =
        "---\n"
        "greeting: hello\n"
        "list:\n"
        "  - one\n"
        "  - two\n"
        "...\n";

    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        std::cerr << "Failed to initialize parser" << std::endl;
        return 1;
    }

    yaml_parser_set_input_string(&parser, yaml_text, sizeof(yaml_text) - 1);

    yaml_event_t event;
    size_t count = 0;
    bool ok = true;
    while (true) {
        if (!yaml_parser_parse(&parser, &event)) {
            std::cerr << "Parse error" << std::endl;
            ok = false;
            break;
        }
        ++count;
        if (event.type == YAML_STREAM_END_EVENT) {
            yaml_event_delete(&event);
            break;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    std::cout << "Parsed events: " << count << "\n";
    return ok ? 0 : 1;
}
