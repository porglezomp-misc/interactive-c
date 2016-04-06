#include "state.h"

#include <stdio.h>

struct state {
  void *(*allocate)(int);
  int a, b;
};

static state *state_init(void *(*allocate)(int)) {
  state *s = allocate(sizeof(state));
  return s;
}

static void state_finalize(state *s) {
  (void) s;
}

static void state_reload(state *s) {
  s->a = 0, s->b = 1;
}

static void state_unload(state *s) {
  (void) s;
}

static bool state_step(state *s) {
  printf("%d\n", s->a);
  int t = s->a;
  s->a = s->b;
  s->b = t + s->b;
  return false;
}

state_api STATE_API = {
  .init = state_init,
  .finalize = state_finalize,
  .reload = state_reload,
  .unload = state_unload,
  .step = state_step,
};
