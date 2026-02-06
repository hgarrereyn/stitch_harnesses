#include <stdio.h>
#include <string.h>
#include <yara.h>

static int callback_fn(YR_SCAN_CONTEXT* context, int message, void* message_data, void* user_data) {
  (void)context; (void)user_data;
  if (message == CALLBACK_MSG_RULE_MATCHING) {
    const YR_RULE* rule = (const YR_RULE*) message_data;
    printf("Matched rule: %s\n", rule->identifier);
  }
  return CALLBACK_CONTINUE;
}

int main() {
  if (yr_initialize() != ERROR_SUCCESS) {
    fprintf(stderr, "yr_initialize failed\n");
    return 1;
  }

  YR_COMPILER* compiler = NULL;
  if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
    fprintf(stderr, "yr_compiler_create failed\n");
    yr_finalize();
    return 1;
  }

  const char* rule_str = "rule always_true { condition: true }";
  int errors = yr_compiler_add_string(compiler, rule_str, NULL);
  if (errors > 0) {
    fprintf(stderr, "Compilation errors: %d\n", errors);
    yr_compiler_destroy(compiler);
    yr_finalize();
    return 1;
  }

  YR_RULES* rules = NULL;
  if (yr_compiler_get_rules(compiler, &rules) != ERROR_SUCCESS) {
    fprintf(stderr, "yr_compiler_get_rules failed\n");
    yr_compiler_destroy(compiler);
    yr_finalize();
    return 1;
  }
  yr_compiler_destroy(compiler);

  const unsigned char data[] = {0x00, 0x01, 0x02, 0x03};
  int scan_res = yr_rules_scan_mem(rules, data, sizeof(data), 0, callback_fn, NULL, 0);
  if (scan_res != ERROR_SUCCESS) {
    fprintf(stderr, "yr_rules_scan_mem failed: %d\n", scan_res);
  }

  yr_rules_destroy(rules);
  yr_finalize();
  return 0;
}
