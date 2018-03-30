#include <stdio.h>
#include "stbuff.h"
#include "file_helper.h"

char * read_line(FILE * to_read) {
  if(to_read == NULL) {
    printf("Null passed to read_line\n");
    return NULL;
  }
  char cchar = fgetc(to_read);
  if(cchar == EOF) {
    return NULL;
  }
  strbuff * wstr = n_strbuff();
  while(cchar != '\n') {
    strbuff_append(wstr, cchar);
    cchar = fgetc(to_read);
  }
  strbuff_append(wstr, '\n');
  char * to_return = get_string(wstr);
  del_strbuff(wstr);
  return to_return;
}
