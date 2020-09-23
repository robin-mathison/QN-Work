#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

#define MINIMUM 26
#define Z_VAL 25

char *letterss[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
  "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

struct Queue {
  Queue *next; // pointer to next node of queue
  uint32_t *stack;
  uint32_t path_len;
};

Queue *q_create(Stack *stack) {
	// creates a queue
	// sets pointer to next q_node to null
	Queue *q = (Queue *)malloc(sizeof(Queue));
	if (!q) {
    perror("error\n");
  } else {
    q->next = NULL; // next element is null
    q->stack = (uint32_t *)malloc(stack->capacity * sizeof(uint32_t));
    q->stack[0] = 0;
    uint32_t i = 1;
    while (i < stack->top + 1) {
    	q->stack[i] = stack->items[i];
    	i++;
    }
    q->path_len = i;
  }
  return q;
}

Queue *q_add(Queue **head, Stack *s) {
  // adds a path to the queue
  if (*head != NULL) {
   // when adding a new element to the front of queue
    if ((*head)->path_len >= (stack_size(s) + 1)) {
      Queue *temp = *head;
      *head = q_create(s);
      (*head)->next = temp;
      return *head;
    }
    Queue *val = *head;
    if ((*head)->next != NULL) {
     // when adding new element to middle of queue
     uint32_t index_count = 0;
     Queue *front = (*head)->next;
     while(front != NULL) {
      if (stack_size(s) + 1 <= front->path_len || front->next == NULL) {
      	for (uint32_t i = 0; i < index_count; i++) {
      		head = &(*head)->next;
      	}
      	if (front->next != NULL || stack_size(s) + 1 <= front->path_len) {
      		Queue *temp = (*head)->next;
      		(*head)->next = q_create(s);
	      	head = &(*head)->next;
	      	(*head)->next = temp;
	      } else {
	      	head = &(*head)->next;
	      	(*head)->next = q_create(s);
	      }
	      head = &val;
	      return *head;
      }
      index_count++;
      front = front->next;
     }
    } else {
     (*head)->next = q_create(s);
     head = &val;
     return *head;
    }
  } else {
    *head = q_create(s);
  }
  return *head;
}

Queue *q_add_new(Queue **new, Queue **head, uint32_t rounds) {
  // queues unreservable paths
	static uint32_t counter = 0;

  Queue *parse = *head;

  for (uint32_t i = 0; i < rounds - counter; i++) {
  	parse = parse->next;
  }

  Queue data = *parse;

  Queue *temp = *new;
 
  Queue *add = (Queue *)malloc(sizeof(Queue));
  *add = data;
  add->next = NULL;
  add->stack = (uint32_t *)malloc(MINIMUM * sizeof(uint32_t));
  add->stack[0] = 0;
  uint32_t i = 1;

  while (i < parse->path_len + 1) {
  	add->stack[i] = parse->stack[i];
  	i++;
  }
  add->path_len = parse->path_len;

  if (*new != NULL) {
  	while((*new)->next != NULL) {
  		new = &(*new)->next;
  	}
  	(*new)->next = add;
  } else {
  	*new = add;
  }
  if (temp == NULL) {
  	temp = *new;
  }
  *new = temp;

  counter++;
  return *new;
}

void q_delete(Queue *head) {
	// deletes a path from the queue
	if (head != NULL) {
		if (head->stack != NULL) {
			free(head->stack);
			head->stack = NULL;
		}
		free(head);
		head = NULL;
	}
	return;
}

void q_free(Queue **head) {
	// deletes and frees all elements of the queue
	if (*head) {
    Queue *temp = *head;
    while (temp != NULL) {
    	*head = temp;
      q_delete(*head);
      temp = (*head)->next;
    }
  }
  return;
}

void q_print(Queue **q) {
	while(*q != NULL) {
		uint32_t i;
  	i = 1;
  	char *charr;
  	uint32_t r;
  	if ((*q)->stack != NULL) {
	  	while (i < (*q)->path_len) {
	    	r = (*q)->stack[i];
	    	charr = letterss[r];
	    	printf("%s -> ", charr);
	    	i++;
	  	}
	   	printf("%s\n", "Z");
	   }
	  q = &(*q)->next;
  }
  return;
}

void q_node_delete(Queue **head, uint32_t rounds, uint32_t num_paths) {
	// deletes a path from the queue for reserve
	// use the index of the node to delete
	Queue *val = *head;
	static uint32_t counter = 0;
	uint32_t u = 0;
	for (u = 0; u < rounds - 1 - counter; u++) {
		if (*head != NULL) {
			head = &(*head)->next;
		}
	}
	if (rounds > 0) { 
		if (rounds < num_paths) {
			Queue *temp1 = *head;
			head = &(*head)->next;
			Queue *temp2 = (*head)->next;
			if ((*head)->stack) {
				free((*head)->stack);
				(*head)->stack = NULL;
			}
			free(*head);
			*head = temp1;
			(*head)->next = temp2;
		} else {
			Queue *temp1 = *head;
			head = &(*head)->next;
			if ((*head)->stack) {
				free((*head)->stack);
				(*head)->stack = NULL;
			}
			free(*head);
			*head = temp1;
			(*head)->next = NULL;
		}
		head = &val; // resets the value of head to start of queue
		counter++;
	}

	return;
}

Queue *q_reserve(Queue **partial, Queue **q, uint32_t num_paths) {
	// parse through queue and reserve paths with least hops
	uint32_t rounds = 0;
	uint32_t channel[26];
	bool not_null = true;
	Queue *tester = *q;
	for (uint32_t fill = 0; fill < MINIMUM; fill++) {
		channel[fill] = 0;
	}
	while (rounds < num_paths && not_null != false) {
		bool cont = true;
		uint32_t i = 1;
		uint32_t temp;
		uint32_t metric = tester->path_len; // counting metric
		while (i < metric && cont == true) {
			temp = tester->stack[i];
			if (channel[temp] != 0) {
				if (temp == 0 || temp == Z_VAL) {
					channel[temp]++;
					i++;
			  } else {

			  	*partial = q_add_new(partial, q, rounds);
					q_node_delete(q, rounds, num_paths);
					cont = false; // stop parsing through
					if (tester == NULL) {
						not_null = false;
					}
			  }
			} else {
				channel[temp]++;
				i++;
			}
		}
		rounds++;
		tester = tester->next;
		if (tester == NULL) {
			not_null = false;
		}
	}
	return *partial;
}

uint32_t q_count(Queue **q) {
	uint32_t count = 0;
	while (*q != NULL) {
		count++;
		q = &(*q)->next;
	}
	return count;
}



