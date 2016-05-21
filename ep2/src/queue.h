#ifndef QUEUE_H_
#define QUEUE_H_

/* Queue of integers. */
typedef struct {
  /* Cyclic array. */
  int *data;
  /* First index. */
  int f;
  /* Last index. */
  int l;
  /* Maximum capacity. */
  int capacity;
} queue_t;

/* Creates a new queue of integers with max number of elements n. */
queue_t* create_queue(int n);

/* Puts v on the end of the queue. */
void queue_push(queue_t *q, int v);
/* Returns and deletes the first element of the queue. */
int queue_pop(queue_t *q);

/* Destroys queue. */
void destroy_queue(queue_t *q);

#endif
