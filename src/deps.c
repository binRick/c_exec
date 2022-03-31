/********************/
#include "../include/deps.h"
/********************/
#include "deps/c_dbg/dbg.c"
/********************/
#include "deps/c_dbg/dbg_module_deps.c"
/********************/
#include "deps/flag/flag.c"
/********************/
#include "process/reproc/src/clock.posix.c"
#include "process/reproc/src/drain.c"
#include "process/reproc/src/error.posix.c"
#include "process/reproc/src/handle.posix.c"
#include "process/reproc/src/init.posix.c"
#include "process/reproc/src/options.c"
#include "process/reproc/src/pipe.posix.c"
#include "process/reproc/src/process.posix.c"
#include "process/reproc/src/redirect.c"
#include "process/reproc/src/redirect.posix.c"
#include "process/reproc/src/reproc.c"
#include "process/reproc/src/run.c"
#include "process/reproc/src/strv.c"
#include "process/reproc/src/utf.posix.c"

/********************/
#define OPTPARSE_IMPLEMENTATION
#include "deps/c_optparse/optparse.h"
/********************/
#include "deps/trim/trim.c"
/********************/

