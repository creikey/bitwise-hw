#include "number_token.h"
#include "number_token_test.h"
#include <ctesting/testing.h>
#include <string.h>
#include <malloc.h>

void test_number_token() {
  t_start_test("number tokens");
  const char * to_test_const = "4234";
  char * to_test = malloc(sizeof(*to_test)*strlen(to_test_const)+1);
  strcpy(to_test, to_test_const);
  int actual = 4234;
  token got = parse_number(to_test, 0, 4);
  T_ASSERT(*(int*)got.data == actual);
  T_ASSERT(got.char_len == 4);
  free(to_test);
  t_end_test();
}
