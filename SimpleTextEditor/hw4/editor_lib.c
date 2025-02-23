#include "editor_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions about ll_text...
// append a line: add to the end of the linked list
ll_text *append_text(ll_text *list, char *text) {
  if (list == NULL){
    ll_text *output = (ll_text*) malloc(sizeof(ll_text));
    output->text = strdup(text);
    output->next = NULL;
    return output;
  }
  if (list->next == NULL){
    ll_text *last = (ll_text*) malloc(sizeof(ll_text));
    last->text = strdup(text);
    last->next = NULL;
    list->next = last;
    return list;
  }
  append_text(list->next, text);


  //UNUSED(list);
  //UNUSED(text);
  return list;
}

void save_to_file(ll_text *list, const char *filename) {
  FILE *outfile = fopen(filename, "w");
  for (ll_text *here = list; here; here = here->next) {
    fprintf(outfile, "%s\n", here->text);
  }
  fclose(outfile);
}

int ll_text_length(ll_text *list) {
  int count = 0;
  while (list != NULL){
    count++;
    list = list->next;
  }  
  //UNUSED(list);
  return count;
}

// insert a specific line: add to specific place in the linked list; this is the
// new entry at the specified line
ll_text *insert_text(ll_text *list, char *text, int position) {
  if (position >= ll_text_length(list)){
    return append_text(list, text);
  }
  if (position == 0){
    ll_text *output = (ll_text*) malloc(sizeof(ll_text));
    output->text = strdup(text);
    output->next = list;
    return output;
  }
  if (position == 1){
    ll_text *input = (ll_text*) malloc(sizeof(ll_text));
    input->text = strdup(text);
    input->next = list->next;
    list->next = input;
    return list;
  }
  insert_text(list->next, text, position-1);
  //UNUSED(list);
  //UNUSED(text);
  //UNUSED(position);
  return list;
}

// delete a specific line: delete the ith entry in the linked list and return
// the new front of the linked list.
ll_text *delete_text(ll_text *list, int position) {
  if (list == NULL){
    return NULL;
  }
  if (list->next == NULL){
    free(list->text);
    free(list->next);
    free(list);
    return NULL;
  }
  if (position == 0){
    ll_text *temp = list->next;
    free(list->text);
    free(list);
    return temp; 
  }
  if (position == 1){
    ll_text *temp = list->next->next;
    free(list->next->text);
    free(list->next);
    list->next = temp;
    return list;
  }
  
  delete_text(list->next, position-1);
  //UNUSED(list);
  //UNUSED(position);
  return list;
}

// replace a line: go to the specific entry, free the text that's there, replace
// it with a copy of the specified text.
ll_text *replace_text(ll_text *list, char *text, int position) {
  if (position == 0){
    free(list->text);
    list->text = strdup(text);
    return list;
  }
  replace_text(list->next, text, position-1);
  //UNUSED(list);
  //UNUSED(text);
  //UNUSED(position);
  return list;
}

// duplicate a list. Returns a copy of the list, including newly copied versions
// of all of the strings.
ll_text *duplicate_ll_text(ll_text *list) {
  if (list == NULL){
    return NULL;
  } else {
    ll_text *copy = (ll_text*) malloc(sizeof(ll_text));
    copy->text = strdup(list->text);
    copy->next = duplicate_ll_text(list->next);
    return copy;
  }
  //UNUSED(list);
}

// functions about the state stack...
ll_text_stack *load_from_file(const char *filename) {
  ll_text *lines = NULL;
  ll_text_stack *stack = calloc(1, sizeof(ll_text_stack));
  char buf[1024];
  FILE *infile = fopen(filename, "r");
  while (fgets(buf, 1024, infile)) {
    chomp(buf);
    lines = append_text(lines, buf);
  }
  stack->lines = lines;
  return stack;
}

ll_text_stack *new_stack_empty_text(void) {
  ll_text_stack *stack = calloc(1, sizeof(ll_text_stack));
  stack->lines = NULL;
  return stack;
}

// Push a new state onto the stack that's an exact copy of the state currently
// at the top.
ll_text_stack *push_duplicate(ll_text_stack *stack) {
  ll_text_stack *new_top = (ll_text_stack*) malloc(sizeof(ll_text_stack));
  new_top->lines = duplicate_ll_text(stack->lines);
  new_top->next = stack;
  //UNUSED(stack);
  return new_top;
}

// Push a new entry onto the stack that has an empty ll_text at the top.
ll_text_stack *push_empty(ll_text_stack *stack) {
  if (stack == NULL){
    ll_text_stack *head = (ll_text_stack*) malloc(sizeof(ll_text_stack));
    head->lines = NULL;
    head->next = NULL;
    return head;
  } else {
    ll_text_stack *new_head = (ll_text_stack*) malloc(sizeof(ll_text_stack));
    new_head->lines = NULL;
    new_head->next = stack;
    return new_head;
  }
  //UNUSED(stack);
}

// undo, removing the most recent state
// this has to free all the memory associated with that state
ll_text_stack *pop_stack(ll_text_stack *stack) {
  if (stack == NULL){
    return NULL;
  } else {
    ll_text_stack *temp = stack->next;
    while(stack->lines != NULL){
      ll_text *temp_text = stack->lines->next;
      free(stack->lines->text);
      free(stack->lines);
      stack->lines = temp_text;
    }
    free(stack);
    return temp;
  }
  //UNUSED(stack);
}

// Find the first newline in the input and replace it with \0
void chomp(char *s) {
  for (int i = 0; s[i]; i++) {
    if (s[i] == '\n' || s[i] == '\r') {
      // Check for \r in case we're on Windows or a very old Mac??
      // Look, I won't stop you from doing CSE 13s on a Mac from 2001 or prior.
      s[i] = '\0';
      break;
    }
  }
}

void blue () {
  printf("\033[0;34m");
}

void white () {
  printf("\033[0;37m");
}
void change_color(char *col){
  if (!strcmp(col, "blue")){
    printf("\033[0;34m");
  } else if (!strcmp(col, "red")){
    printf("\033[0;31m");
  } else if (!strcmp(col, "green")){
    printf("\033[0;32m");
  } else if (!strcmp(col, "yellow")){
    printf("\033[0;33m");
  } else if (!strcmp(col, "black")){
    printf("\033[0;30m");
  } else if (!strcmp(col, "purple")){
    printf("\033[0;35m");
  } else if (!strcmp(col, "cyan")){
    printf("\033[0;36m");
  } else {
    white();
  } 
}
