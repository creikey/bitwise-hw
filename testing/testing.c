#include "testing.h"
#include <stdio.h>

void t_init() {
  _t_suit_name = "null";
  _t_name = "null";
  _t_failed = false;
  _t_failures = 0;
  printf("[ test begin ]\n");
}

void t_start_suit(const char * to_change_to) {
  _t_suit_name = to_change_to;
  printf("--- Test Suite (%s) ---\n", to_change_to);
}

void t_end_suit() {
  if(_t_failures > 0) {
    printf(":( Test suit (%s) failed with (%d) failures\n", _t_suit_name, _t_failures);
  } else {
    printf(":) Test suit (%s) success!\n", _t_suit_name);
  }
  _t_suit_name = "null";
  _t_failures = 0;
}

void t_start_test(const char * test_name) {
  _t_name = test_name;
  printf("| starting test (%s)\n", test_name);
}

void t_end_test() {
  printf("| ending test (%s)\n", _t_name);
  _t_name = "null";
}

void _t_assert(bool expr, int line_numb, const char * file, const char * expr_text) {
  if(!expr) {
    printf("! [ Line %d : File %s : Test %s ] | Assert Failed\n", line_numb, file, _t_name);
    printf("! - Expr (%s)\n", expr_text);
    _t_failed = true;
    _t_failures++;
  }
}

void t_end() {
  printf("[ testing end ]\n\n");
  _t_suit_name = NULL;
  _t_name = NULL;
  _t_failed = false;
  _t_failures = 0;
}
