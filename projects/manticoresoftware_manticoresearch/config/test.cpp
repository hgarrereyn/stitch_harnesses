#include <iostream>
extern "C" {
#include <sphinxclient.h>
}

int main() {
    sphinx_client* c = sphinx_create(SPH_TRUE);
    if (!c) {
        std::cout << "Failed to create client" << std::endl;
        return 1;
    }
    sphinx_set_server(c, "127.0.0.1", 9306); // default SQL port; won't connect in this test
    sphinx_set_match_mode(c, SPH_MATCH_ALL);
    sphinx_set_limits(c, 0, 10, 1000, 0);

    const char* err = sphinx_error(c);
    const char* warn = sphinx_warning(c);
    std::cout << "Initialized sphinx client. err=" << (err?err:"")
              << " warn=" << (warn?warn:"") << std::endl;

    sphinx_cleanup(c);
    sphinx_destroy(c);
    std::cout << "OK" << std::endl;
    return 0;
}
