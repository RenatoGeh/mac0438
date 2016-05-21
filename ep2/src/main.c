#include <stdio.h>
#include <stdlib.h>

/* Debug: 1 true; 0 false. */
#define DEBUG 1
#include "debug.h"

#include "utils.h"
#include "room.h"
#include "student.h"
#include "guard.h"
#include "lock.h"

/** Notes to self:
 * - Time is always milliseconds unless explicitly specified.
 */

int main(int argc, char *args[]) {
  int n;  /* Invitees. */
  int p;  /* Minimum. */
  ms_t t; /* Max arrival time. */
  ms_t r; /* Max stay time. */
  ms_t s; /* Max guard patrol time. */

  int i;

  /* Students. */
  student_t **st_v;
  /* Guard. */
  guard_t *g;

  if (argc != 6) {
    puts("Uso:\n ./ep2 <convidados> <minimo-alunos> <intervalo> <tempo_festa> <tempo-ronda>\n"
        "Onde:\n"
        "   <convidados>: numero total de convidados para a festa\n"
        "<minimo-alunos>: numero minimo de alunos na festa para o seguranca esvaziar a sala\n"
        "    <intervalo>: intervalo maximo de tempo entre chegadas de convidados em ms\n"
        "  <tempo-festa>: tempo maximo de participacao na festa para cada aluno em ms\n"
        "  <tempo-ronda>: tempo maximo de ronda do seguranca em ms\n");
    return 1;
  }

  n = atol(args[1]), p = atol(args[2]);
  t = atol(args[3]), r = atol(args[4]);
  s = atol(args[5]);

  /* Creates and initializes. */
  g_room = create_room(n);
  SLOG("Created room.");
  st_v = (student_t**) malloc(n*sizeof(student_t*));
  for (i=0;i<n;++i) {
    st_v[i] = create_student(t, r);
    LOG("Created student %d", i);
  }
  g = create_guard(s, p);
  SLOG("Created George, the guard.");

  /* Starts all threads. */
  for (i=0;i<n;++i)
    start_student(st_v[i]);
  start_guard(g);

  /* Joins all threads. */
  for (i=0;i<n;++i) {
    join_student(st_v[i]);
    LOG("Student %d went home.", i);
  }

  /* Notifies guard duty is over. He may go home. */
  mutex_lock(&end_lock);
  SLOG("George, your shift is over.");
  has_ended = 1;
  /* In case George decides to make it to the 2016 Olympics and runs his round too fast. */
  room_signal();
  mutex_unlock(&end_lock);

  /* Go home, George. */
  join_guard(g);
  SLOG("'Night George.");

  /* Cleans and destroys. */
  for (i=0;i<n;++i)
    destroy_student(st_v[i]);
  free(st_v);
  destroy_guard(g);
  destroy_room(g_room);

  return 0;
}

