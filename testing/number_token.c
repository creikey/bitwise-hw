#include "number_token.h"
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
  /*for(int i = num_len; i >= 0; i--) {
    *cur_numb += (to_parse[cur+look_ahead]-'0')*(10*i);
    look_ahead++;
  }*/
  for (size_t i=cur; i < cur+num_len; i++)
  {
    *cur_numb *= 10;  //left shift 1
    *cur_numb += to_parse[i] - '0';
  }

  to_return.data = cur_numb;
  return to_return;
}

void test_number_token() {
  const char * to_test_const = "4234";
  char * to_test = malloc(sizeof(*to_test)*strlen(to_test_const)+1);
  strcpy(to_test, to_test_const);
  int actual = 4234;
  token got = parse_number(to_test, 0, 4);
  if(*(int*)got.data != actual) {
    printf("number_token test failed: got (%d), wanted (%d)\n", *(int*)got.data, actual);
  } else {
    printf("number_token test passed!\n");
  }
  if(got.char_len != 4) {
    printf("number_token test failed: got length (%lu), wanted (%d)\n", got.char_len, 4);
  }
}
