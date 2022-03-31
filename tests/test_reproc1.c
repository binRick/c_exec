/*******************/
#define _POSIX_C_SOURCE     200809L
#define LOG_TIME_ENABLED    false
#define QTY                 10
#define VERSION             "v1.0.0"
/*******************/
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <unistd.h>
/*******************/
#include "include/module_imports.h"
/*******************/
#include "src/deps.c"
/*******************/
#include "./flag_subcommands.c"
/*******************/


static inline void millisleep(long ms){
  nanosleep(&(struct timespec){
    .tv_sec  = (ms) / 1000,
    .tv_nsec = ((ms) % 1000L) * 1000000,
  },
            NULL
            );
}
enum { NUM_CHILDREN = QTY };


static int parent(const char *program){
  reproc_event_source children[NUM_CHILDREN] = { { 0 } };
  int                 r                      = -1;

  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_t   *process = reproc_new();

    const char *date_args[]  = { "date", NULL };
    const char *sleep_args[] = { "sleep", "0.01", NULL };

    r = reproc_start(process, date_args, (reproc_options){ .nonblocking = true });
    if (r < 0) {
      goto finish;
    }

    children[i].process   = process;
    children[i].interests = REPROC_EVENT_OUT;
  }

  for ( ;;) {
    r = reproc_poll(children, NUM_CHILDREN, REPROC_INFINITE);
    if (r < 0) {
      r = r == REPROC_EPIPE ? 0 : r;
      goto finish;
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
      if (children[i].process == NULL || !children[i].events) {
        continue;
      }
      uint8_t output[4096];
      r = reproc_read(children[i].process, REPROC_STREAM_OUT, output, sizeof(output));
      if (r == REPROC_EPIPE) {
        children[i].process = reproc_destroy(children[i].process);
        continue;
      }

      if (r < 0) {
        goto finish;
      }
      output[r] = '\0';

      char msg[1024];
      sprintf(&msg, "<%d> %s", getpid(), trim(output));
      log_ok(trim(msg));
    }
  }

finish:
  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_destroy(children[i].process);
  }

  if (r < 0) {
    log_error("%s", reproc_strerror(r));
  }


  return(abs(r));
} /* parent */


static int child(void){
  srand(((unsigned int)getpid()));
  int ms = rand() % NUM_CHILDREN * 4; // NOLINT

  millisleep(ms);
  log_info("Process %i slept %i milliseconds.", getpid(), ms);
  return(EXIT_SUCCESS);
}


int main(int argc, const char **argv){
  return(argc > 1 && strcmp(argv[1], "child") == 0 ? child() : parent(argv[0]));
}
