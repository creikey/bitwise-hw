#include <stdio.h>
#include <string.h>
#include "config.h"
#include "stbuff.h"
#include "file_helper.h"
#include "number_token.h"


int main(int argc, char ** argv) {
  test_stbuff();
  test_number_token();
  FILE * fp = fopen(TO_READ, "r");
  if(fp == NULL) {
    printf("Cannot read file %s\n", TO_READ);
    return -1;
  }
  char * cur_line = read_line(fp);
  int line = 1;
  while(cur_line != NULL) {
    printf("Reading (%s) from file %s...\n", cur_line, TO_READ);
    cur_line = read_line(fp);
    tokbuff * toks = tokenize(cur_line, line, strlen(cur_line));
     print_tokens(toks);
    line++;
  }
  return 0;
}
