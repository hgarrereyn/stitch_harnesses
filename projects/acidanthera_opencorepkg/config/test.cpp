#include <Acidanthera/Library/OcXmlLib.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
  const char *xml = "<plist><dict><key>Name</key><string>OpenCore</string></dict></plist>";
  XML_DOCUMENT *doc = XmlDocumentParse((CHAR8*)xml, (UINT32)62, (BOOLEAN)0);
  if (!doc) { printf("parse failed\n"); return 0; }
  UINT32 out_len = 0;
  CHAR8 *out = XmlDocumentExport(doc, &out_len, 0, 1);
  printf("exported length=%u\n", (unsigned)out_len);
  if (out) free(out);
  XmlDocumentFree(doc);
  return 0;
}
