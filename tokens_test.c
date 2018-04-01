#include "tokens_test.h"
#include "number_token_test.h"
#include "tokens.h"
#include <ctesting/testing.h>
#include <malloc.h>

void test_tokens() {
  t_start_suit("tokens");
  test_number_token();
  test_tokbuff();
  test_cmptok();
  t_end_suit();
}

void test_tokbuff() {
  t_start_test("tokbuff");
  tokbuff * actual = malloc(sizeof *actual);
  actual->data = malloc(sizeof *actual->data * 2);
  actual->len = 2;
  actual->max_len = 2;
  int first_data = 5;
  int second_data = 6;
  actual->data[0] = (token) {SYMBOL, 2, &first_data};
  actual->data[1] = (token) {NUMBER, 1, &second_data};
  tokbuff * got = n_tokbuff();
  append_token(got, (token) {SYMBOL, 2, &first_data});
  append_token(got, (token) {NUMBER, 1, &second_data});
  T_ASSERT(actual->len == got->len);
  T_ASSERT(actual->max_len == got->max_len);
  T_ASSERT(cmptok(actual->data[0], get_token(got, 0)));
  T_ASSERT(cmptok(actual->data[1], get_token(got, 1)));
  t_end_test();
}

void test_cmptok() {
  t_start_test("cmptok");
  // int raw_left_data = 3;
  // int raw_right_data = 4;
  int * left_data = malloc(sizeof *left_data);
  int * right_data = malloc(sizeof *right_data);
  *left_data = 3;
  *right_data = 4;
  token tok1 = (token) {SYMBOL, 2, left_data};
  token tok2 = (token) {SYMBOL, 2, right_data};
  T_ASSERT(cmptok(tok1, tok2) == false);
  *left_data = *right_data;
  T_ASSERT(cmptok(tok1, tok2) == true);
  tok1.type = NUMBER;
  T_ASSERT(cmptok(tok1, tok2) == false);
  tok1.type = SYMBOL;
  T_ASSERT(cmptok(tok1, tok2) == true);
  t_end_test();
}
