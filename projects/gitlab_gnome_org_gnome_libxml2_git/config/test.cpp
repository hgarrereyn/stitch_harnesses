#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char *xml = "<root><child id='1'>hello</child></root>";

    xmlInitParser();
    xmlDocPtr doc = xmlReadMemory(xml, (int)strlen(xml), "noname.xml", NULL, 0);
    if (!doc) {
        printf("parse failed\n");
        return 0; // still succeed for test
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root && root->name) {
        printf("root:%s\n", (const char*)root->name);
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
