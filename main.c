#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "state.h"

const char *libfile = "libstateful.so";

state_api STATE_API;
void *wrapper_malloc(int size) { return calloc(1, size); }

int main() {
  void *library = dlopen(libfile, RTLD_LAZY);
  state_api *api = dlsym(library, "STATE_API");
  memcpy(&STATE_API, api, sizeof(STATE_API));
  struct state *s = STATE_API.init(wrapper_malloc);
  STATE_API.step(s);
  STATE_API.finalize(s);
  return 0;
}
