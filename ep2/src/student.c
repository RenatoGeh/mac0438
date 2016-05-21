#include "student.h"

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <pthread.h>
#include <time.h>

#include "utils.h"
#include "lock.h"
#include "room.h"

int has_ended = 0;

student_t* create_student(ms_t t, ms_t r) {
  student_t *st;
  static int id_count = 0;

  st = (student_t*) malloc(sizeof(student_t));
  st->id = id_count++;

  t = ulrand(0, t);
  r = ulrand(0, r);

  /* To seconds. */
  st->st.tv_sec = t/((long int)1e3);
  st->dt.tv_sec = r/((long int)1e3);
  /* To nanoseconds. */
  st->st.tv_nsec = (t - st->st.tv_sec*1e3)*1e6;
  st->dt.tv_nsec = (r - st->dt.tv_sec*1e3)*1e6;

  return st;
}

int start_student(student_t *st) {
  return pthread_create(&(st->pid), NULL, student_func, (void*) st);
}

void* student_func(void* arg) {
  student_t *self;
  int id;

  self = (student_t*) arg;
  id = self->id;

  nanosleep(&(self->st), NULL);

  tprintf(" Aluno %d na porta.\n", id);
  room_push(g_room, self);

  nanosleep(&(self->dt), NULL);

  room_pop(g_room, self);
  tprintf(" Aluno %d vai embora.\n", id);

  return NULL;
}

void join_student(student_t *s) {
  pthread_join(s->pid, NULL);
}

void destroy_student(student_t *s) {
  free(s);
}
