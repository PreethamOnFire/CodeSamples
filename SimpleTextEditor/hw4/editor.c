#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "editor_lib.h"

void print_help(char *colo) {
  change_color(colo);
  printf("valid commands are...\n");
  printf("- help: display this message\n");
  printf("- color: change the color of editor\n");
  printf("- list: display current text in memory with line numbers\n");
  printf("- undo: revert to the previous state (undoing cannot be undone)\n");
  printf("- append: add a new line to the end of the text\n");
  printf("- insert: add a new line to the text at an existing line number\n");
  printf("- replace: change the text at an existing line number\n");
  printf("- delete: remove an existing line\n");
  printf("- clear: make the buffer be empty (this can be undone)\n");
  printf("- save: write the file to disk\n");
  printf("- quit: exit the program\n");
  white();
}

// Prompt the user for a line number; keep asking until we get a useful answer.
int prompt_for_line_number(char *msg, int length) {
  bool good_number = false;
  int linenum;
  char buf[1024];
  while (!good_number) {
    printf("%s\n", msg);
    fgets(buf, 1024, stdin);
    chomp(buf);
    linenum = strtol(buf, NULL, 10) - 1;
    if (linenum >= 0 && linenum < length) {
      good_number = true;
    } else {
      printf("invalid line number.\n");
    }
  }
  return linenum;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "USAGE: editor <filename>\n");
    return 0;
  }
  const char *filename = argv[1];
  
  blue();
  printf("**************************************\n");
  printf("* welcome to the cse13s text editor! *\n");
  printf("**************************************\n");
  printf("editing %s\n", filename);
  white();

  const int BUFSIZE = 1024;
  char buf[BUFSIZE];
  char *result;
  char color[30] = "blue";

  ll_text_stack *stack = NULL;
  if (access(filename, F_OK) == 0) {
    stack = load_from_file(filename);
    change_color(color);
    printf("loaded %s from disk\n", filename);
    white();
  } else {
    stack = new_stack_empty_text();
  }
  while (true) {
    change_color(color);
    printf("command: ");
    white();
    result = fgets(buf, BUFSIZE, stdin);
    if (!result) {
      break;
    }
    chomp(result);

    if (!strcmp(buf, "quit") || !strcmp(buf, "q")) {
      break;
    } else if (!strcmp(buf, "help") || !strcmp(buf, "?")) {
      print_help(color);
    } else if (!strcmp(buf, "list")) {
      ll_text *here = stack->lines;
      for (int i = 1; here; i++) {
	change_color(color);
        printf("%4d|", i);
        white();
	printf("%s\n", here->text);
        here = here->next;
      }
    } else if (!strcmp(buf, "save")) {
      save_to_file(stack->lines, filename);
      change_color(color);
      printf("saved to %s\n", filename);
    } else if (!strcmp(buf, "append")) {
      change_color(color);
      printf("type the new line to add to the file.\n");
      white();
      result = fgets(buf, BUFSIZE, stdin);
      chomp(buf);

      // make a new stack entry so we can undo
      stack = push_duplicate(stack);
      stack->lines = append_text(stack->lines, buf);
    } else if (!strcmp(buf, "insert")) {
      int length = ll_text_length(stack->lines);
      if (!length) {
	change_color(color);
        printf("can't insert; there are currently no lines. "
               "use append instead.\n");
        continue;
      }
      change_color(color);
      int linenum = prompt_for_line_number(
          "at which line number (1-indexed) would you like to insert?", length);
      change_color(color);
      printf("type the new line to add to the file at that line number.\n");
      white();
      result = fgets(buf, BUFSIZE, stdin);
      chomp(buf);

      // make a new stack entry so we can undo
      stack = push_duplicate(stack);
      stack->lines = insert_text(stack->lines, buf, linenum);
    } else if (!strcmp(buf, "replace")) {
      int length = ll_text_length(stack->lines);
      if (!length) {
	change_color(color);
        printf("can't replace; there are currently no lines.\n");
        continue;
      }
      change_color(color);
      int linenum = prompt_for_line_number(
          "which line number (1-indexed) would you like to replace?", length);
      change_color(color);
      printf("type the new line to put at that line number.\n");
      white();
      result = fgets(buf, BUFSIZE, stdin);
      chomp(buf);

      // make a new stack entry so we can undo
      stack = push_duplicate(stack);
      stack->lines = replace_text(stack->lines, buf, linenum);
    } else if (!strcmp(buf, "delete")) {
      int length = ll_text_length(stack->lines);
      if (!length) {
	change_color(color);
        printf("can't delete; there are currently no lines.\n");
        continue;
      }
      change_color(color);
      int linenum = prompt_for_line_number(
          "which line number (1-indexed) would you like to delete?", length);

      // make a new stack entry so we can undo
      stack = push_duplicate(stack);
      stack->lines = delete_text(stack->lines, linenum);
    } else if (!strcmp(buf, "clear")) {
      // push an empty ll_text onto the stack
      stack = push_empty(stack);
    } else if (!strcmp(buf, "undo")) {
      // pop from the stack
      stack = pop_stack(stack);
      if (!stack) {
        stack = new_stack_empty_text();
      }
    } else if (!strcmp(buf, "color")) {
	change_color(color);
        printf("What color do you want? \n");
	white();
        fgets(color, sizeof(color), stdin);
	chomp(color);
	change_color(color);
        printf("Changed to %s\n", color);	
    } else {
      change_color(color);
      printf("unknown command: %s\n", buf);
    }
  }
  // done with the loop. Clean up by undoing until the stack is empty.
  while (stack) {
    stack = pop_stack(stack);
  }
  change_color(color);
  printf("bye!\n");
  return 0;
}
