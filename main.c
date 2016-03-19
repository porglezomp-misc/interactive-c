#include <stdio.h>
#include "state.h"

int main() {
  struct state *s = STATE_API.init();
  STATE_API.step(s);
  return 0;
}
