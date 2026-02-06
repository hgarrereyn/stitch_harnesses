#include <iostream>
#include <cstring>
#include <miniupnpc/miniupnpc.h>
#include <miniupnpc/igd_desc_parse.h>

int main() {
    const char *xml = "<?xml version=\"1.0\"?>\n"
                      "<root>\n"
                      "  <device>\n"
                      "    <deviceType>urn:schemas-upnp-org:device:InternetGatewayDevice:1</deviceType>\n"
                      "    <friendlyName>Fake IGD</friendlyName>\n"
                      "  </device>\n"
                      "</root>\n";
    IGDdatas data{};
    parserootdesc(xml, (int)std::strlen(xml), &data);
    std::cout << "MiniUPnPc version: " << MINIUPNPC_VERSION << "; API: " << MINIUPNPC_API_VERSION << "\n";
    std::cout << "Parsed rootdesc for Fake IGD (no crash)" << std::endl;
    return 0;
}
