#include "stack.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *letters[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
  "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

Stack *stack_create(void) {
  // From Darrell Long
  Stack *s = (Stack *)malloc(sizeof(Stack));
  if (!s) {
    perror("malloc");
    exit(-1);
  }

  s->top = 0;
  s->capacity = MINIMUM;

  s->items = (uint32_t *)malloc(s->capacity * sizeof(uint32_t));
  if (!s->items) {
    perror("malloc");
    exit(-1);
  }

  return s;
}

void stack_delete(Stack *s) {
  if (s->items != NULL) {
    free(s->items);
    s->items = NULL;
  }
  if (s != NULL) {
    free(s);
    s = NULL;
  }
  return;
}

bool stack_empty(Stack *s) {
  bool empty = true;
  if (s->items[s->top] != 0) {
    empty = false;
  }

  return empty;
}

uint32_t stack_size(Stack *s) {
  return s->top;
}

bool stack_push(Stack *s, uint32_t item) {
  if (s->top == s->capacity) {
    s->capacity *= 2;
    s->items = (uint32_t *)realloc(s->items, s->capacity * sizeof(uint32_t));
  }
  s->top = s->top + 1; // change top of stack to index at new item
  s->items[s->top] = item;
  return true;
}

bool stack_pop(Stack *s) {
  if (stack_empty(s)) {
    return false;
  } else {
    s->items[s->top] = 0;
    s->top -= 1;
    return true;
  }
}

void stack_print(Stack *s) {
  uint32_t i;
  i = 1;
  char *charr;
  uint32_t r;
  while (i < s->top + 1) {
    r = s->items[i];
    charr = letters[r];
    printf("%s -> ", charr);
    i++;
  }

  return;
}

