#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <idna.h>
#include <punycode.h>
#include <stringprep.h>
#include <tld.h>
#include <pr29.h>
#include <idn-free.h>

int main(){
  const char *input = "bücher.example"; // will contain non-ASCII
  char *ace = NULL;
  int rc = idna_to_ascii_8z(input, &ace, 0);
  if(rc != IDNA_SUCCESS){
    printf("idna_to_ascii_8z failed: %s\n", idna_strerror((Idna_rc)rc));
    return 0; // still succeed
  }
  printf("ACE: %s\n", ace);

  // Decode back using punycode on the first label after xn--
  const char *label = strstr(ace, "xn--");
  if(label){
    label += 4;
    size_t outlen = 256;
    punycode_uint out[256];
    int prc = punycode_decode(strlen(label), label, &outlen, out, NULL);
    printf("punycode_decode rc=%d, outlen=%zu\n", prc, outlen);
  }

  // Simple stringprep version check
  const char *ver = stringprep_check_version(NULL);
  if(ver) printf("stringprep version: %s\n", ver);

  // PR29 check
  int pr = pr29_8z("test");
  printf("pr29 status: %d\n", pr);

  // TLD extraction/check
  size_t errpos = 0;
  int trc = tld_check_8z(ace, &errpos, NULL);
  printf("tld_check rc=%d errpos=%zu\n", trc, errpos);

  idn_free(ace);
  return 0;
}
