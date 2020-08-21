#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

#define MINIMUM 26

typedef struct Queue Queue;

Queue *q_create(Stack *stack);
// creates a queue

Queue *q_add(Queue **q, Stack *stack);
// adds a path to the queue

void q_delete(Queue *q);
// deletes a path from the queue

void q_free(Queue **q);
// deletes and frees all elements of the queue

void q_print (Queue **q);

void q_reserve(Queue **q, uint32_t num_paths);

uint32_t q_count(Queue **q);

#endif
