#ifndef H_TOKENIZER
#define H_TOKENIZER

#include <stdbool.h>

// token_kind is a list of the different tokens supported
typedef enum token_kind {
  SQUIG,
  MULTIPLY,
  DIVIDE,
  MODULO,
  RIGHT_SHIFT,
  LEFT_SHIFT,
  BIN_AND,
  ADD,
  SUBTRACT,
  BIN_OR,
  POW,
  NUMBER,
  UNKNOWN
} token_kind;

// token is a basic container containing either a kind with zero or kind=NUMBER
// and a vlue
typedef struct token {
  token_kind kind;
  int val;
} token;

// arr_token is a sized array of tokens
typedef struct arr_token {
  token *toks;
  int len;
} arr_token;

// tokenize is a function that takes in a stream of characters and returns an
// array of tokens
arr_token tokenize(char *to_tokenize);

// get_token_kind is a function that gets the kind of token based on a null
// terminated string input
token_kind get_token_kind(char *to_token);

// is_digit checks to see if the input character is a digit
bool is_digit(char to_check);

// to_digit converts the input character to an integer type
int to_digit(char to_convert);

// num_places gets the number of digits in a number
int num_places(int n);

// resolve_numb resolves a number of n length from an input string and cursor
int resolve_numb(char *charstream, int cur);

#endif // H_TOKENIZER
