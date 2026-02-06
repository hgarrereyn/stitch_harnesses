#include <stdio.h>
#include <_CFXMLInterface/CFXMLInterface.h>

int main() {
    // Call into the minimal stubbed function to ensure link works
    int line = _CFXMLInterfaceSAX2GetLineNumber(NULL);
    printf("Line: %d\n", line);
    return 0;
}
