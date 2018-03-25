#include "logging.h"
#include "tokenizer.h"

void test_tokenizer() {
  const char *to_test = ">><<+1352+1";
  token want_arr[] = {{RIGHT_SHIFT, 0}, {LEFT_SHIFT, 0}, {ADD, 0},
                      {NUMBER, 1352},   {ADD, 0},        {NUMBER, 1}};
  arr_token want = {want_arr, 6, 8};
  arr_token get = tokenize(to_test);
  if (want.len != get.len) {
    t_log("wanted length %d, got length %d\n", want.len, get.len);
  }
  if (want.max_len != get.max_len) {
    t_log("wanted max length %d, got max length %d\n", want.max_len,
          get.max_len);
  }
  for (size_t i = 0; i < sizeof(want_arr) / sizeof(*want_arr); i++) {
    if (want_arr[i].kind != get.toks[i].kind) {
      t_log("wanted token kind %d, got token kind %d\n", want_arr[i].kind,
            get.toks[i].kind);
    }
    if (want_arr[i].val != get.toks[i].val) {
      t_log("wanted token value %d, got token value %d\n", want_arr[i].val,
            get.toks[i].val);
    }
  }
}
