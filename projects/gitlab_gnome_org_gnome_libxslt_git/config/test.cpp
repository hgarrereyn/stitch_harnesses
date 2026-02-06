#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltutils.h>
#include <libxslt/transform.h>

int main() {
    const char *xmlStr = "<root><name>World</name></root>";
    const char *xslStr =
        "<?xml version=\"1.0\"?>"
        "<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">"
        "  <xsl:template match=\"/\">"
        "    <greeting>Hello, <xsl:value-of select=\"root/name\"/>!</greeting>"
        "  </xsl:template>"
        "</xsl:stylesheet>";

    xmlInitParser();
    LIBXML_TEST_VERSION

    xmlDocPtr xml = xmlReadMemory(xmlStr, (int)strlen(xmlStr), "input.xml", NULL, 0);
    xmlDocPtr xslDoc = xmlReadMemory(xslStr, (int)strlen(xslStr), "style.xsl", NULL, 0);
    if (!xml || !xslDoc) {
        fprintf(stderr, "Failed to parse XML or XSLT\n");
        if (xml) xmlFreeDoc(xml);
        if (xslDoc) xmlFreeDoc(xslDoc);
        xmlCleanupParser();
        return 1;
    }

    xsltStylesheetPtr style = xsltParseStylesheetDoc(xslDoc);
    if (!style) {
        fprintf(stderr, "Failed to parse stylesheet\n");
        xmlFreeDoc(xml);
        xmlCleanupParser();
        return 1;
    }

    xmlDocPtr res = xsltApplyStylesheet(style, xml, NULL);
    if (!res) {
        fprintf(stderr, "Failed to apply stylesheet\n");
        xsltFreeStylesheet(style);
        xmlFreeDoc(xml);
        xmlCleanupParser();
        return 1;
    }

    xmlChar *out = NULL;
    int outLen = 0;
    if (xsltSaveResultToString(&out, &outLen, res, style) == 0 && out) {
        printf("%.*s\n", outLen, (char*)out);
        xmlFree(out);
    } else {
        fprintf(stderr, "Failed to serialize result\n");
    }

    xmlFreeDoc(res);
    xsltFreeStylesheet(style);
    xmlFreeDoc(xml);

    xsltCleanupGlobals();
    xmlCleanupParser();
    return 0;
}
