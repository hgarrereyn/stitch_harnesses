#include <iostream>
#include <libical/ical.h>

int main() {
    const char *ics = "BEGIN:VCALENDAR\nVERSION:2.0\nPRODID:-//Example Corp.//libical test//EN\nBEGIN:VEVENT\nUID:12345@example.com\nDTSTAMP:20240101T000000Z\nDTSTART:20240102T120000Z\nDTEND:20240102T130000Z\nSUMMARY:Test Event\nEND:VEVENT\nEND:VCALENDAR\n";

    icalcomponent *comp = icalcomponent_new_from_string(ics);
    if (!comp) {
        std::cout << "Failed to parse iCalendar string\n";
        return 0; // don't fail the test
    }

    if (!icalcomponent_is_valid(comp)) {
        std::cout << "Component not valid\n";
    }

    char *out = icalcomponent_as_ical_string(comp);
    if (out) {
        // Print a short prefix to show it worked
        std::cout << std::string(out).substr(0, 32) << "...\n";
    }

    icalcomponent_free(comp);
    return 0;
}
