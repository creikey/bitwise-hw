#include "tokens.h"
#include "number_token.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctesting/testing.h>
#include "number_token.h"

void test_tokens() {
  t_start_suit("tokens");
  test_number_token();
  t_end_suit();
}

tokbuff * tokenize(char * to_tokenize, int line, size_t length) {
  tokbuff * to_return = n_tokbuff();
  size_t cur = 0;
  token tok = (token) {UNKNOWN, 0, NULL};
  while(cur < length) {
    tok = (token) {UNKNOWN, 0, NULL};
    if(is_digit(to_tokenize[cur])) {
      // get the number
      tok = parse_number(to_tokenize, cur, length);
    } else {
      // get the symbol
      // tok = parse_symbol(to_tokenize, cur, length);
    }
    if(tok.type == UNKNOWN) {
      printf("Unknown token at column %lu, line %d\n", cur, line);
      cur++;
    } else {
      cur += tok.char_len;
    }
    append_token(to_return, tok);
  }
  return to_return;
}

tokbuff * n_tokbuff() {
  tokbuff * to_return = malloc(sizeof *to_return);
  to_return->len = 1;
  to_return->max_len = 1;
  to_return->data = malloc(sizeof *to_return->data * to_return->len);
  return to_return;
}

void d_tokbuff(tokbuff * to_delete) {
  free(to_delete->data);
  free(to_delete);
}

void append_token(tokbuff *buff, token to_append) {
  if( buff->len >= buff->max_len) {
    buff->max_len *= 2;
    buff->data = realloc(buff->data, buff->max_len);
  }
  buff->data[buff->len-1] = to_append;
  buff->len++;
}

token get_token(tokbuff *to_read, size_t index) {
  if(index >= to_read->len) {
    printf("Invaled request for token out of range\n");
    return (token){UNKNOWN, 0, NULL};
  }
  return to_read->data[index];
}

void print_tokens(tokbuff *to_print) {
  token tok;
  for(size_t i = 0; i < to_print->len; i++) {
    tok = get_token(to_print, i);
    printf("[%lu](", i);
    switch(tok.type) {
      case SYMBOL:
        printf("symbol-todo");
        break;
      case NUMBER:
        printf("%d", *(int*)tok.data);
        break;
      case UNKNOWN:
        printf("unknown");
        break;
      default:
        printf("error - type not in range");
    }
    printf(") ");

  }
  printf("\n");
}
