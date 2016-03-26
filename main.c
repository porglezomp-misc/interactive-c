#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dlfcn.h>

#include "state.h"

const char *libfile = "libstateful.so";

state_api STATE_API;
void *wrapper_malloc(int size) { return calloc(1, size); }

static bool first_load = true;
static volatile bool should_reload = true;
static bool running = true;

int main() {
  void *library = NULL;
  state_api *api = NULL;
  struct state *s = NULL;

  while (running) {
    should_reload = true;
    if (should_reload) {
      should_reload = false;
      if (library) {
        dlclose(library);
      }
      library = dlopen(libfile, RTLD_LAZY);
      if (!library) {
        printf("Error opening library: %s\n", dlerror());
        continue;
      }
      api = dlsym(library, "STATE_API");
      if (!api) {
        printf("error: %s\n", dlerror());
        continue;
      }
      memcpy(&STATE_API, api, sizeof(STATE_API));
      if (first_load) {
        first_load = false;
        s = STATE_API.init(wrapper_malloc);
      }
    }
    STATE_API.step(s);
    sleep(1);
  }
  STATE_API.finalize(s);
  return 0;
}

