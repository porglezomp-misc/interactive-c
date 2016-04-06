#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <dlfcn.h>

#include "state.h"

const char *libfile = "libstateful.so";

typedef struct program_state {
  void *library;
  state_api api;
  struct state *state;
} program_state;

static void *wrapper_malloc(int size) { return calloc(1, size); }

static int reload_program(program_state *program) {
  bool first_load = false;
  if (program->library) {
    program->api.unload(program->state);
    dlclose(program->library);
  } else {
    first_load = true;
  }

  program->library = dlopen(libfile, RTLD_LAZY);
  if (!program->library) return 1;
  state_api *api = dlsym(program->library, "STATE_API");
  if (!api) return 2;
  memcpy(&program->api, api, sizeof(program->api));
  if (first_load) {
    program->state = program->api.init(wrapper_malloc);
  }
  program->api.reload(program->state);
  return 0;
}

static volatile bool should_reload = true;
static bool running = true;

void enable_reload(int _) {
  (void) _;
  signal(SIGUSR1, enable_reload);
  should_reload = true;
}

int main() {
  signal(SIGUSR1, enable_reload);
  program_state *program = calloc(1, sizeof *program);
  while (running) {
    if (should_reload) {
      should_reload = false;
      if (reload_program(program)) {
        printf("%s\n", dlerror());
        continue;
      }
    }
    program->api.step(program->state);
    sleep(1);
  }
  program->api.finalize(program->state);
  return 0;
}

