#include <stdio.h>
#include <time.h>
#include <cups/cups.h>
#include <cups/json.h>
int main() {
  // Use a couple of APIs so we link against libcups
  printf("CUPS version: %d.%d.%d\n", CUPS_VERSION_MAJOR, CUPS_VERSION_MINOR, CUPS_VERSION_PATCH);
  // Create a tiny JSON doc using the JSON API
  cups_json_t *root = cupsJSONNew(NULL, NULL, CUPS_JTYPE_OBJECT);
  cups_json_t *key = cupsJSONNewKey(root, NULL, "hello");
  (void)cupsJSONNewString(root, key, "world");
  char *s = cupsJSONExportString(root);
  if (s) {
    printf("JSON: %s\n", s);
    free(s);
  }
  cupsJSONDelete(root);
  return 0;
}
