#include <stdio.h>
#include <stdlib.h>

#include "state.h"

int main() {
  struct state *s = STATE_API.init();
  STATE_API.step(s);
  STATE_API.finalize(s);
  return 0;
}

void *wrapper_malloc(int size) {
  return malloc(size);
}
