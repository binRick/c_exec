/*******************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*******************/
/*******************/
enum CMD_IDS {
  CMD_ECHO  = 0,
  CMD_SLEEP = 1,
};
/*******************/
#define COMMANDS           \
  { "echo", cmd_echo, },   \
  { "sleep", cmd_sleep, }, \
/*******************/


static void subcommands_usage(FILE *f) {
  fprintf(f,
          AC_RESETALL AC_MAGENTA "usage: example [-h] "
          AC_RESETALL AC_RED AC_BOLD "<%s|%s>"
          AC_RESETALL AC_MAGENTA " [OPTION]..."
          AC_RESETALL "\n",
          "echo",
          "sleep"
          );
}


static int cmd_echo(char **argv){
  int             i, option;
  bool            newline = true;
  struct optparse options;

  optparse_init(&options, argv);
  options.permute = 0;
  while ((option = optparse(&options, "hn")) != -1) {
    switch (option) {
    case 'h':
      puts("usage: echo [-hn] [ARG]...");
      return(0);

    case 'n':
      log_debug("NEWLINE DISABLED");
      newline = false;
      break;
    case '?':
      log_error("%s: %s\n", argv[0], options.errmsg);
      return(1);
    }
  }
  argv += options.optind;

  for (i = 0; argv[i]; i++) {
    log_info(AC_RESETALL AC_BLUE AC_REVERSED AC_BOLD "%s%s" AC_RESETALL, i  ? " " : "", argv[i]);
  }
  if (newline) {
    log_debug("Adding Newline!");
    putchar('\n');
  }else{
    log_debug("Skipping Newline!");
  }

  fflush(stdout);
  return(!!ferror(stdout));
}


static int cmd_sleep(char **argv){
  int             i, option;
  struct optparse options;

  optparse_init(&options, argv);
  while ((option = optparse(&options, "h")) != -1) {
    switch (option) {
    case 'h':
      puts("usage: sleep [-h] [NUMBER]...");
      return(0);

    case '?':
      log_error("%s: %s\n", argv[0], options.errmsg);
      return(1);
    }
  }

  for (i = 0; argv[i]; i++) {
    if (sleep(atoi(argv[i]))) {
      return(1);
    }
  }
  return(0);
}
