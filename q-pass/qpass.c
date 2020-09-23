#include "stack.h"
#include "queue.h"
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// current model assumes that k = 26 for kth neighbors known

#define ASCII_NUM 65 // deals with input
#define MATRIX_MAX 26 // max size of matrix

struct Queue {
  Queue *next; // pointer to next node of queue
  uint32_t *stack;
  uint32_t path_len;
};


bool check_u, check_d, check_m, check_t; // checks if options specified
uint32_t path_count, path_length; // counters

void error();
void dfs(Stack *path_stack, uint32_t curr_node, Queue **head);
Queue *head;


// Matrix representing nodes
uint32_t matrix[MATRIX_MAX][MATRIX_MAX];

char *letter[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
  "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

 // array to keep track of path
uint32_t check_array[26];

void error() {
  printf("error\n");
}

// finds paths through matrix
void dfs(Stack *path_stack, uint32_t curr_node, Queue **head) {
  if (curr_node == MATRIX_MAX - 1) {
    uint32_t curr_path = (stack_size(path_stack) + 1);
    printf("Found path: ");
    stack_print(path_stack);
    printf("Z\n"); // including at end of every path
    // add current stack state to the queue
    // must compare path length to put in correct order
    printf("PATH LENGTH: %d\n", stack_size(path_stack) + 1);
    *head = q_add(head, path_stack);
    printf("Paths:\n");
    q_print(head);
    printf("Shortest Path Length: %d \n\n", (*head)->path_len);
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
      if(stack_size(path_stack) != 1 || curr_node != 0) {
        stack_push(path_stack, curr_node);
      }
      dfs(path_stack, j, head); // recursion
      stack_pop(path_stack);
     }
    j++;
  }
  return;
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

  dfs(path_stack, 0, &head);
  printf("Final Possible Paths:\n");
  q_print(&head);

  Queue *partial = NULL;
  partial = q_reserve(&partial, &head, path_count);
  
  printf("\nRESERVED PATH(S):\n");
  q_print(&head);

  printf("\nPARTIAL PATH(S):\n");
  q_print(&partial);

  q_free(&head);  
  q_free(&partial);
  stack_delete(path_stack);

  printf("Number of paths found: %d \n", path_count);
  printf("Length of shortest path found: %d \n", path_length);
  return 0; 
}

