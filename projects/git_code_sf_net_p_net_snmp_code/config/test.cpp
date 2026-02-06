#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <cstdio>

int main() {
    init_snmp("netsnmp_test");

    netsnmp_session session;
    snmp_sess_init(&session);
    session.version = SNMP_VERSION_1;

    netsnmp_pdu* pdu = snmp_pdu_create(SNMP_MSG_GET);
    if (pdu) {
        snmp_free_pdu(pdu);
    }

    const char* ver = netsnmp_get_version();
    if (ver) {
        std::printf("Net-SNMP version: %s\n", ver);
    } else {
        std::printf("Net-SNMP version unavailable\n");
    }

    snmp_shutdown("netsnmp_test");
    return 0;
}
