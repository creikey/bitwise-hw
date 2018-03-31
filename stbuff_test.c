#include "stbuff_test.h"
#include "stbuff.h"
#include <ctesting/testing.h>
#include <string.h>

void test_stbuff() {
  t_start_suit("stbuff");
  test_strbuff();
  t_end_suit();
}

void test_strbuff() {
  t_start_test("strings");
  const char * to_make = "ass";
  strbuff * to_test = n_strbuff();
  strbuff_append(to_test, to_make[0]);
  strbuff_append(to_test, to_make[1]);
  strbuff_append(to_test, to_make[2]);
  T_ASSERT(strcmp(to_make, get_string(to_test)) == 0);
  t_end_test();
}
