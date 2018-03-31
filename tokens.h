#ifndef H_TOKENS
#define H_TOKENS

#include <stdbool.h>
#include <stddef.h>

typedef enum token_type { SYMBOL, NUMBER, UNKNOWN } token_type;

typedef struct token {
  token_type type;
  size_t char_len;
  void *data;
} token;

typedef struct tokbuff {
  size_t len;
  size_t max_len;
  token *data;
} tokbuff;

tokbuff *n_tokbuff();

void d_tokbuff(tokbuff *to_delete);

void append_token(tokbuff *buff, token to_append);

token get_token(tokbuff *to_read, size_t index);

void print_tokens(tokbuff *to_print);

// tokenize returns a token array of input
tokbuff *tokenize(char *to_tokenize, int line, size_t length);

void test_tokens();

void test_cmptok();

void test_tokbuff();

bool cmptok(token left, token right);

#endif // H_TOKENS
