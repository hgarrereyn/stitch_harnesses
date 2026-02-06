#include <stdio.h>
#include <string.h>
#include <jerryscript.h>

int main() {
  jerry_init(JERRY_INIT_EMPTY);

  const char script[] = "1 + 2";
  jerry_value_t ret = jerry_eval((const jerry_char_t*)script, (size_t)strlen(script), JERRY_PARSE_NO_OPTS);

  if (jerry_value_is_number(ret)) {
    double num = jerry_value_as_number(ret);
    printf("Result: %.0f\n", num);
  } else {
    printf("Eval did not return a number.\n");
  }

  jerry_value_free(ret);
  jerry_cleanup();
  return 0;
}
