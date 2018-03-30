#include <stdio.h>
#include "config.h"
#include "stbuff.h"
#include "file_helper.h"


int main(int argc, char ** argv) {
  test_stbuff();
  FILE * fp = fopen(TO_READ, "r");
  if(fp == NULL) {
    printf("Cannot read file %s\n", TO_READ);
    return -1;
  }
  char * cur_line = read_line(fp);
  while(cur_line != NULL) {
    printf("Reading (%s) from file %s...\n", cur_line, TO_READ);
    cur_line = read_line(fp);
  }
  return 0;
}
