#include <iostream>
#include <ps3netsrv/VIsoFile.h>
#include <ps3netsrv/File.h>
#include <ps3netsrv/compat.h>

int main() {
    // Use some types defined in headers to verify we can include them
    FileList fl{}; // struct from VIsoFile.h
    SectorRangeEntry s{}; // from VIsoFile.h
    (void)fl; (void)s;

    // Use a macro from compat.h if available, otherwise just print
#ifdef PATH_SEPARATOR
    std::cout << "ps3netsrv headers OK. PATH_SEPARATOR='" << PATH_SEPARATOR << "'\n";
#else
    std::cout << "ps3netsrv headers OK." << std::endl;
#endif
    return 0;
}
