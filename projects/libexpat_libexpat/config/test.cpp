#include <stdio.h>
#include <string.h>
#include <expat.h>

static void XMLCALL startElement(void *userData, const XML_Char *name, const XML_Char **atts) {
    (void)userData; (void)atts;
    printf("Start: %s\n", name);
}

static void XMLCALL endElement(void *userData, const XML_Char *name) {
    (void)userData;
    printf("End: %s\n", name);
}

int main() {
    const char *xml = "<root><child id=\"1\">text</child></root>";
    XML_Parser parser = XML_ParserCreate(NULL);
    if (!parser) {
        fprintf(stderr, "Failed to create parser\n");
        return 1;
    }

    XML_SetElementHandler(parser, startElement, endElement);

    if (XML_Parse(parser, xml, (int)strlen(xml), XML_TRUE) == XML_STATUS_ERROR) {
        fprintf(stderr, "Parse error at line %lu: %s\n",
                (unsigned long)XML_GetCurrentLineNumber(parser),
                XML_ErrorString(XML_GetErrorCode(parser)));
        XML_ParserFree(parser);
        return 1;
    }

    XML_ParserFree(parser);
    return 0;
}
