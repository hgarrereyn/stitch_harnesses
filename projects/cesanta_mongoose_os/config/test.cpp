#include <frozen.h>
#include <stdio.h>
#include <string.h>

static int s_count = 0;
static void cb(void *ud, const char *name, size_t name_len, const char *path, const struct json_token *tok) {
  (void)ud; (void)path; (void)tok; (void)name; (void)name_len;
  s_count++;
}

int main() {
  const char *json = "{\"foo\":123, \"bar\":[1,2,3], \"baz\":true}";
  int n = json_walk(json, (int) strlen(json), cb, NULL);
  if (n < 0) {
    printf("json_walk error: %d\n", n);
    return 1;
  }
  struct json_out out = JSON_OUT_BUF(NULL, 0);
  char buf[128];
  out.u.buf.buf = buf; out.u.buf.size = sizeof(buf); out.u.buf.len = 0;
  json_printf(&out, "{foo:%d,bar:%Q}", 42, "hello");
  buf[out.u.buf.len] = '\0';
  printf("walked=%d tokens=%d, out=%s\n", n, s_count, buf);
  return 0;
}
