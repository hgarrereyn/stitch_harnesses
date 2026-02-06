#include <argp.h>
#include <stdio.h>
#include <string.h>

const char *argp_program_version = "argp-test 1.0";
const char *argp_program_bug_address = "n/a";

static char doc[] = "Simple argp test program";
static char args_doc[] = "[STRING]";

static struct argp_option options[] = {
  {"upper", 'u', 0, 0, "Print in upper case", 0},
  {0}
};

struct arguments { int upper; const char *input; };

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = (struct arguments*)state->input;
  switch (key) {
    case 'u': arguments->upper = 1; break;
    case ARGP_KEY_ARG: arguments->input = arg; break;
    case ARGP_KEY_END: break;
    default: return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main() {
  struct arguments arguments = {0, "hello"};
  const char *argv[] = {"prog", "-u", "world", NULL};
  int argc = 3;
  char *argv_nc[4];
  for (int i = 0; i < 4; ++i) argv_nc[i] = (char*)argv[i];
  argp_parse(&argp, argc, argv_nc, 0, 0, &arguments);
  if (!arguments.input) arguments.input = "hello";
  char buf[64];
  snprintf(buf, sizeof(buf), "%s", arguments.input);
  if (arguments.upper) {
    for (char *p = buf; *p; ++p) if (*p >= 'a' && *p <= 'z') *p -= 32;
  }
  printf("Result: %s\n", buf);
  return 0;
}
