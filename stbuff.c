#include "stbuff.h"
#include <ctesting/testing.h>
#include <malloc.h>
#include <string.h>

strbuff * n_strbuff() {
  strbuff * to_return = malloc(sizeof *to_return);
  to_return->len = 1;
  to_return->max_len = 1;
  to_return->str = malloc(sizeof *to_return->str);
  return to_return;
}

void strbuff_append(strbuff * buff, char to_append) {
  // printf("Appending %c\n", to_append);
  if(buff->len >= buff->max_len) {
    buff->max_len *= 2;
    buff->str = realloc(buff->str, buff->max_len);
  }
  buff->str[buff->len-1] = to_append;
  buff->len++;
}

char * get_string(strbuff * to_read) {
  char * to_return = malloc((sizeof *to_return * to_read->len)+1);
  strncpy(to_return, to_read->str, to_read->len);
  to_return[to_read->len] = '\0';
  return to_return;
}

void del_strbuff(strbuff * to_del) {
  free(to_del->str);
  free(to_del);
}
