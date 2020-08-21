#ifndef __STACK_H__
#define __STACK_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define MINIMUM 26

typedef struct Stack {
  uint32_t *items;
  uint32_t top; // keeps track of the top index of a stack
  uint32_t capacity; // keeps track of a stack's capacity
} Stack;

Stack *stack_create(void);

void stack_delete(Stack *s);

bool stack_empty(Stack *s);

uint32_t stack_size(Stack *s);

bool stack_push(Stack *s, uint32_t item);

bool stack_pop(Stack *s);

void stack_print(Stack *s);

#endif
