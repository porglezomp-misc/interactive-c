#include "state.h"

#include <stdio.h>

struct state {
  int nothing_interesting;
};

static state *state_init(void *(*allocate)(int)) {
  state *s = allocate(sizeof(state));
  return s;
}

static void state_finalize(state *s) {
  (void) s;
}

static void state_reload(state *s) {
  (void) s;
}

static void state_unload(state *s) {
  (void) s;
}

static bool state_step(state *s) {
  puts("Hello, World!");
  return s != 0;
}

state_api STATE_API = {
  .init = state_init,
  .finalize = state_finalize,
  .reload = state_reload,
  .unload = state_unload,
  .step = state_step,
};
