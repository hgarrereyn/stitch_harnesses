#include <cstdio>
#include <cups/ipp.h>
#include <cups/cups.h>
int main() {
  ipp_t *ipp = ippNew();
  if (!ipp) {
    printf("Failed to create IPP object\n");
    return 1;
  }
  ippSetVersion(ipp, 2, 0);
  ippSetRequestId(ipp, 123);
  printf("CUPS version macro: %d.%d.%d\n", CUPS_VERSION_MAJOR, CUPS_VERSION_MINOR, CUPS_VERSION_PATCH);
  printf("IPP length: %zu, request-id: %d\n", ippGetLength(ipp), ippGetRequestId(ipp));
  return 0;
}
