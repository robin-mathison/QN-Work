#include "binary.h"
#include "extra.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint32_t swapp, count;

// swapping function 
void swap(uint32_t *a, uint32_t j, uint32_t i) {
  uint32_t swap = a[j];
  a[j] = a[i];
  a[i] = swap;
  return;
}

void swap(Queue *front, Queue *back) {
  Queue *temp = front;

}

void binary(uint32_t *a, uint32_t l) {
  for (uint32_t i = 1; i < l; i++) {
    uint32_t value = a[i];
    uint32_t left = 0;
    uint32_t right = i;
    while (left < right) {
      uint32_t mid = left + ((right - left) / 2);
      if (value >= a[mid]) {
        count++;
        left = mid + 1;
      } else {
        count++;
        right = mid;
      }
    }
    for (uint32_t j = i; j > left; j--) {
      swap(a, (j - 1), j);
      swapp += 3;
    }
  }

  return;
}


// does binary insertion sort
  if (i_s == true) {
    swap_count = 0;
    swapp = 0;
    count = 0;
    uint32_t *array = (uint32_t *)calloc(
        n, sizeof(uint32_t)); // dynamically allocates memory for the array
    for (uint32_t i = 0; i < n; i++) {
      array[i] = arr[i];
    }
    binary(array, n);
    swap_count += swapp;
    printf("Binary Insertion Sort\n");
    printf("%d elements %d moves %d compares", n, swap_count, count);
    for (uint32_t i = 0; i < p; i++) {
      if (i % 6 == 0) {
        printf("\n  ");
      }
      printf("%10d  ", array[i]);
    }

    printf("\n\n");
    free(array);
  }

Queue *q_add(Queue *head, Stack *s) {
  // adds a path to the queue
  if (head != NULL) {
    while(head->next != NULL) {
      // new stuff
      head = head->next;
    }
    head->next = q_create(s); 
  } else {
    head = q_create(s);
  }
  return head;
}


  Queue *q_add(Queue *head, Stack *s) {
  // adds a path to the queue
    if (head != NULL) {
      Queue *back = NULL;
      Queue *front = NULL;
      while(head->next != NULL) {
        // new stuff
        // when adding a new element to the front of queue
        if (stack_size(head->stack) >= stack_size(s)) {
          Queue *temp = head;
          head = q_create(s);
          head->next = temp;
        }
        head = head->next;
        back = head;
        front = head->next;
        // all other cases
        if (stack_size(head->stack) >= stack_size(s)) {
          Queue *temp = front;
          head->next = q_create(s);
          head = head->next;
          head->next = front;
        }
        //
      }
      head->next = q_create(s); 
    } else {
      head = q_create(s);
    }
    return head;
}

#include "stack.h"
#include "queue.h"
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ASCII_NUM 65 // deals with input
#define MATRIX_MAX 26 // max size of matrix

bool check_u, check_d, check_m, check_t; // checks if options specified
uint32_t path_count, path_length; // counters

void error();
void dfs();

uint32_t matrix[MATRIX_MAX][MATRIX_MAX];

char *letter[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
  "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

struct Queue {
  Queue *next; // pointer to next node of queue
  Stack *stack; // stack (path) going into queue node
};

uint32_t check_array[26]; // keeps track of path

// finds paths through matrix
void dfs(Stack *path_stack, uint32_t curr_node, Queue *head) {
  if (curr_node == MATRIX_MAX - 1) {
    uint32_t curr_path = (stack_size(path_stack) + 1);
    printf("Found path: ");
    stack_print(path_stack);
    printf("Z\n"); // including at end of every path
    // add current stack state to the queue
    // must compare path length to put in correct order
    head = q_add(head);
    uint32_t temp_int = 1;
    while(temp_int < stack_size(path_stack)) {
      stack_push(head->stack, path_stack->items[temp_int]);
      temp_int++;
    }
    check_array[25] = 0;
    path_count++;
    if (curr_path < path_length) {
      path_length = curr_path;
    }
    return;
  }
  uint32_t j = 0;
  while (j < (MATRIX_MAX)) {
    if (matrix[curr_node][j] == 1 && check_array[j] == 0) {
      check_array[j] = 1;
      stack_push(path_stack, curr_node);
      dfs(path_stack, j, head); // recursion
      stack_pop(path_stack);
    }
    j++;
  }
  return;
}

void error() {
  printf("error\n");
}

int main(int argc, char **argv) {
  int c = 0;
  FILE *infile = stdin;
  check_u = false;
  check_d = false;
  check_m = false;
  check_t = false;
  while ((c = getopt(argc, argv, "i:udm")) != -1) {
    switch (c) {
    case 'i':
      infile = fopen(optarg, "r");
      if (infile == NULL) {
        perror(optarg);
        exit(1);
      }
      break;
    case 'u': // undirected
      check_u = true;
      if (check_d == true) {
        error();
      }
      break;
    case 'd': // directed
      check_d = true;
      if (check_u == true) {
        error();
      }
      break;
    case 'm':
      check_m = true;
      break;
    }
  }

  if (argc == 1) {
    puts("No arguments supplied! \n");
    puts("arguments: -i -u -d -m \n");
    return -1;
  }

  char s[256];
  uint32_t m, n;

  for (int i = 0; i < MATRIX_MAX; i++) {
    for (int j = 0; j < MATRIX_MAX; j++) {
      matrix[i][j] = 0;
    }
  }

  if (check_d == true) {
    check_u = false;
  } else {
    check_u = true;
  }

  while (fscanf(infile, "%s", s) != EOF) { // user input
    //printf("%s\n", s);
    if (isalpha(s[0]) && isalpha(s[1])) { // checks for good input
      m = (toupper(s[0]) - ASCII_NUM); // converts
      n = (toupper(s[1]) - ASCII_NUM); // converts
      matrix[m][n] = 1;
      if (check_u == true) {
        matrix[n][m] = 1;
      }
    }
  }

  // creats matrix
  if (check_m == true) {
    printf("\n");
    printf("  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z\n");
    for (int i = 0; i < MATRIX_MAX; i++) {
      printf("%s ", letter[i]);
      for (int j = 0; j < MATRIX_MAX; j++) {
        printf("%d ", matrix[i][j]);
      }
      printf("\n");
    }
  }


  for (int i = 0; i < 26; i++) {
    check_array[i] = 0;
  }

  Stack *path_stack = stack_create();
  Queue *head = NULL;
 
  path_count = 0;
  path_length = 26;

  dfs(path_stack, 0, head);
  bool delete = true;
  printf("\n");
  printf("goop\n");
  if(head->stack != NULL) {
    printf("foofie\n");
    stack_print(head->stack);
  } else {
    printf("dooooop\n");
  }
  //q_print(head);
  printf("\n");

  while (delete == true){
    delete = q_delete(head, path_stack);
  }
  printf("Number of paths found: %d \n", path_count);
  printf("Length of shortest path found: %d \n", path_length);
  return 0; 
}

