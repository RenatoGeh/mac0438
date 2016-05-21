#include "room.h"

#include <stdlib.h>
#include <stdio.h>

#include "student.h"
#include "queue.h"
#include "lock.h"

room_t *g_room;

/* Room mutex. */
mutex_t room_lock = PTHREAD_MUTEX_INITIALIZER;
/* Empty conditional variable. */
cond_t empty_cv = PTHREAD_COND_INITIALIZER;

#define LOCK mutex_lock(&room_lock)
#define UNLOCK mutex_unlock(&room_lock)

room_t* create_room(int n) {
  room_t *r;
  int i;

  r = (room_t*) malloc(sizeof(room_t));
  r->s_v = (student_t**) malloc(n*sizeof(student_t*));

  for (i=0;i<n;++i)
    r->s_v[i] = NULL;

  r->n = 0;

  r->q = create_queue(n);
  for (int i=0;i<n;++i)
    queue_push(r->q, i);

  return r;
}

void room_push(room_t *r, student_t *s) {
  LOCK;
  r->s_v[queue_pop(r->q)] = s;
  ++(r->n);
  UNLOCK;
}

void room_pop(room_t *r, student_t *s) {
  student_t **s_v = r->s_v;
  int i, n;

  LOCK;
  for (i=0,n=r->n;i<n;++i)
    if (s_v[i] == s) {
      /* Get out, s_v[i]! */
      queue_push(r->q, i);
      --(r->n);
      s_v[i] = NULL;
      tprintf("N: %d\n", r->n);
      if (r->n == 0) {
        room_signal();
      }
      UNLOCK;
      return;
    }
  UNLOCK;
}

void room_signal(void) {
  cond_signal(&empty_cv);
}

int room_size(room_t *r) {
  return r->n;
}

void room_wait(room_t *r) {
  LOCK;
  tputs("Seguranca expulsa alunos.");
  while (r->n > 0) {
    cond_wait(&empty_cv, &room_lock);
  }
  UNLOCK;
}

void destroy_room(room_t *r) {
  int i, n;

  n = r->n;
  destroy_queue(r->q);
  for (i=0;i<n;++i)
    free(r->s_v[i]);
  free(r->s_v);
  free(r);

  mutex_destroy(&room_lock);
  cond_destroy(&empty_cv);
}
