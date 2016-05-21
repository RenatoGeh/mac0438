/*******************************************************************/
/** MAC 438 - Programacao Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Segundo Exercicio-Programa                                    **/
/** Arquivo: room.c                                               **/
/**                                                               **/
/** Renato Lui Geh | 8536030                                      **/
/**                                                               **/
/** 24/05/2016                                                    **/
/*******************************************************************/

#include "room.h"

#include <stdlib.h>
#include <stdio.h>

#include "student.h"
#include "queue.h"
#include "lock.h"

room_t *g_room;

/* Did we actually have a party? */
int had_party;

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

  had_party = 0;

  return r;
}

void room_push(room_t *r, student_t *s) {
  LOCK;
  r->s_v[s->id] = s;
  ++(r->n);
  ++had_party;
  UNLOCK;
}

void room_pop(room_t *r, student_t *s) {
  student_t **s_v = r->s_v;
  LOCK;
  /* Get out, s_v[i]! */
  s_v[s->id] = NULL;
  --(r->n);
  if (r->n == 0)
    room_signal();
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
  tputs("Seguranca inspeciona a sala.");
  if (r->n > 0)
    tputs("Seguranca expulsa alunos.");
  while (r->n > 0)
    cond_wait(&empty_cv, &room_lock);
  UNLOCK;
}

int room_had_party(void) {
  return had_party > 0;
}

void destroy_room(room_t *r) {
  free(r->s_v);
  free(r);

  mutex_destroy(&room_lock);
  cond_destroy(&empty_cv);
}
