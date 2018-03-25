#include "tokenizer.h"
#include "logging.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <limits.h>

// token_kind_names is an array of the strings in token_kind
const char *token_kind_names[] = {[SQUIG] = "~",        [MULTIPLY] = "*",
                                  [DIVIDE] = "/",       [MODULO] = "%",
                                  [RIGHT_SHIFT] = ">>", [LEFT_SHIFT] = "<<",
                                  [BIN_AND] = "&",      [ADD] = "+",
                                  [SUBTRACT] = "-",     [BIN_OR] = "|",
                                  [POW] = "^"};

arr_token tokenize(char * to_tokenize) {
  // to_return is the arr token to return
  arr_token to_return;
  // set arr_token to zero values
  to_return.len = 0;
  to_return.toks = NULL;
  // check to see if input string is null
  if(to_tokenize == NULL) {
    return to_return;
  }
  // make toks an array of malloc equal to one token
  to_return.toks = malloc(sizeof(*to_return.toks));
  // cur is a variable that holds the current token
  token cur;
  // cur_tok_kind is a variable that holds the current token kind
  token_kind cur_tok_kind;
  // max_tok_len is the maximum character length of any token
  int max_tok_len = get_max_tok_len(token_kind_names);
  // cur_str is the current string to ber passed to get_toke_kind
  char * cur_str = malloc(sizeof(*cur_str) * (max_tok_len+1));
  // loop over the input string
  for( unsigned int  i = 0; i < strlen(to_tokenize); i++ ) {
    // ii is the iterator for the cur_tok_kind loop
    unsigned int ii;
    // loop over possible amount of characters
    for( ii = 1; ii <= max_tok_len; ii++ ) {
      strncpy(cur_str, to_tokenize, ii); // copy string into buffer
      cur_str[ii] = 0; // null terminate string
      cur_tok_kind = get_token_kind(cur_str); // get the token kind
      if(cur_tok_kind != UNKNOWN) { // if it's not unknown, exit the for loop
        break;
      }
    }
    if( cur_tok_kind == UNKNOWN ) {
      s_log("Unknown token %s", cur_str);
    } else if( cur_tok_kind == NUMBER ) {
      // set the curren token's val
      cur.val = resolve_numb(to_tokenize, i);
    i += ii; // advance the current counter so it's the token ahead
  }
  return to_return;
}

int get_max_tok_len(const char ** to_find_max_len) {
  unsigned int cur_max_len = 0;
  for(unsigned int i = 0; i < sizeof(to_find_max_len)*sizeof(*to_find_max_len); i++) {
    if(strlen(to_find_max_len[i]) > cur_max_len) {
      cur_max_len = strlen(to_find_max_len[i]);
    }
  }
  return cur_max_len;
}

// TODO add negative support
int resolve_numb( char * charstream, int cur ) {
  // to_return is a variable that holds the number to return
  int to_return;
  // ishift is a variable holding the amount of left shift on base 10 needed
  int ishift;
  // if the input isn't a digit, return -1
  if(!is_digit(charstream[cur])) {
    return -1;
  }
  while(is_digit(charstream[cur])) {
    to_return += to_digit(charstream[cur]) << 10*ishift;
    ishift++;
    cur++;
  }
  return to_return;
}

token_kind get_token_kind(char * to_token) {
  // check to see if input string is null
  if(to_token == NULL) {
    return UNKNOWN;
  }
  // check to see if input is a digit
  if(is_digit(to_token[0])) {
    return NUMBER;
  }
  // sort through the names and see if the current char matches any of them
  for( unsigned int i = 0; i < sizeof(token_kind_names); i++ ) {
    // return the token kind if found a match
    if( strcmp(to_token, token_kind_names[i]) == 0 ) {
      return (token_kind)i;
    }
  }
  // return unknown if all else fails
  return UNKNOWN;
}

int to_digit(char to_convert) {
  // Make sure input is a digit
  assert(is_digit(to_convert));
  return to_convert - '0';
}

bool is_digit(char to_check) {
  if(to_check > '0' && to_check < '9') {
    return true;
  } else {
    return false;
  }
}

int num_places (int n) {
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    /*      2147483647 is 2^31-1 - add more ifs as needed
       and adjust this final return as well. */
    return 10;
}

void append_token(arr_token to_append_to, token to_append) {
  // if the current length is greater or equal to the maximum length
  if( to_append_to.len >= to_append_to.max_len ) {
    // resize the array of tokens to twice its max size
    to_append_to.toks = realloc(to_append_to.toks, to_append_to.max_len*2);
    to_append_to.max_len = to_append_to.max_len*2;
  }
  to_append_to.toks[to_append_to.len] = to_append;
  to_append_to.toks++;
}
