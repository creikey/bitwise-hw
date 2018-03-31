#include "number_token.h"
#include <ctesting/testing.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

bool is_digit(char to_check) {
  if (to_check < '9' && to_check > '0') {
    return true;
  }
  return false;
}

token parse_number(char *to_parse, int cur, size_t length) {
  size_t look_ahead = 0;
  size_t num_len = 0;
  while(look_ahead+cur < length && is_digit(to_parse[cur+look_ahead])) {
    num_len += 1;
    look_ahead++;
  }
  look_ahead=0;
  int * cur_numb = malloc( sizeof *cur_numb );
  *cur_numb = 0;
  token to_return = (token) {NUMBER, num_len, cur_numb};
  for (size_t i=cur; i < cur+num_len; i++)
  {
    *cur_numb *= 10;  //left shift 1
    *cur_numb += to_parse[i] - '0';
  }

  to_return.data = cur_numb;
  return to_return;
}
