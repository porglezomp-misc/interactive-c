#ifndef _INTERACTIVE_STATE_H
#define _INTERACTIVE_STATE_H

#include <stdbool.h>

struct state;
typedef struct state state;

/* should be defined in the wrapper */
void *wrapper_malloc(int size);

typedef struct state_api {
  struct state *(*init)();
  void (*finalize)(struct state *s);
  void (*reload)(struct state *s);
  void (*unload)(struct state *s);
  bool (*step)(struct state *s);
} state_api;

/* should be defined in the library */
extern const state_api STATE_API;

#endif
