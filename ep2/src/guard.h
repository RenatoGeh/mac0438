#ifndef GUARD_H_
#define GUARD_H_

#include <sys/types.h>
#include <time.h>

#include "utils.h"

typedef struct {
  /* pthread ID. */
  pthread_t pid;
  /* Patrol time. */
  timespec_t dt;
  /* Minimum students. */
  int p;
} guard_t;

/* Creates a guard. */
guard_t* create_guard(ms_t s, int p);

int start_guard(guard_t *g);

void* guard_func(void* arg);

void join_guard(guard_t *g);

void destroy_guard(guard_t *g);

#endif
