#ifndef _INTERACTIVE_STATE_H
#define _INTERACTIVE_STATE_H

#include <stdbool.h>

struct state;
typedef struct state state;

typedef struct state_api {
  struct state *(*init)(void *(*allocator)(int size));
  void (*finalize)(struct state *s);
  void (*reload)(struct state *s);
  void (*unload)(struct state *s);
  bool (*step)(struct state *s);
} state_api;

/* should be defined in the library */
extern state_api STATE_API;

#endif
