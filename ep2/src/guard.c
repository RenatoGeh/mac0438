#include "guard.h"

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <pthread.h>
#include <time.h>

#include "utils.h"
#include "lock.h"
#include "room.h"
#include "student.h"

#define DEBUG 1
#include "debug.h"

guard_t* create_guard(ms_t s, int p) {
  guard_t *g;

  g = (guard_t*) malloc(sizeof(guard_t));

  s = ulrand(0, s);

  /* To seconds. */
  g->dt.tv_sec = s/((long int)1e3);
  /* To nanoseconds. */
  g->dt.tv_nsec = (s - g->dt.tv_sec*1e3)*1e6;

  g->p = p;

  return g;
}

int start_guard(guard_t *g) {
  return pthread_create(&(g->pid), NULL, guard_func, (void*) g);
}

void* guard_func(void* arg) {
  guard_t *self;

  self = (guard_t*) arg;

  /* Otherwise undefined behavior. */
  mutex_lock(&end_lock);

  while (!has_ended) {
    mutex_unlock(&end_lock);

    SLOG("Starting me shift, boss.");

    nanosleep(&(self->dt), NULL);

    SLOG("Has my shift ended, boss?");

    mutex_lock(&end_lock);
    if (has_ended) {
      mutex_unlock(&end_lock);
      break;
    }
    mutex_unlock(&end_lock);

    SLOG("Apparently not. Wait. What's that noise?");

    tputs("Seguranca na porta.");
    room_wait(g_room);
    tputs("Seguranca em ronda.");

    mutex_lock(&end_lock);
  }

  /* Not really necessary. But I don't want to keep this little guy locked in. */
  mutex_unlock(&end_lock);

  return NULL;
}

void join_guard(guard_t *g) {
  pthread_join(g->pid, NULL);
}

void destroy_guard(guard_t *g) {
  free(g);
  mutex_destroy(&end_lock);
}
