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
                                  [POW] = "^", [UNKNOWN] = "?jdklfjdlsfj"};

arr_token tokenize(const char * to_tokenize) {
  p_log("Starting to tokenize %s\n", to_tokenize);
  arr_token to_return = {0,0,0}; // to_return is a zero value array of tokens
  if(to_tokenize == NULL) {
    s_log("received null value in function %s\n", __FUNCTION__);
    return to_return;
  }
  int max_tok_len = get_max_tok_len(token_kind_names); // maximum token length
  unsigned int tok_cur = 0; // current character in the string
  char * cur_str; // current string in the to_tokenize string
  /* make size of max length + 1 for safety */
  int cur_str_size = sizeof(*cur_str)*max_tok_len+1;
  cur_str = malloc(cur_str_size);
  memset(cur_str, '\0', cur_str_size-1); // set the string to null
  int look_ahead = 1; // current look ahead for cur_str
  token cur_token; // current token
  p_log("tok cur is %d, to_tokenize len is %d\n", tok_cur, strlen(to_tokenize));
  while(tok_cur < strlen(to_tokenize)) { // iterate over tokenization string
    p_log("token cursor at %d, look ahead at %d", tok_cur, look_ahead);
    /* set the string specified by look_ahead to cur_str */
    memset(cur_str, '\0', cur_str_size); // set the string to null
    strncpy(cur_str, to_tokenize, look_ahead);
    p_log("successfully set the cur_str to %s\n", cur_str);
    /* iterate through the token_kind_names array and set the current token */
    for(unsigned int i = FIRST_TOKEN_KIND; i < LAST_TOKEN_KIND; i++) {
      if(token_kind_names[i] != NULL ) {
        p_log("Searching for tokens on index %d, current token kind: %s\n", i, token_kind_names[i]);
        if(strcmp(cur_str, token_kind_names[i]) == 0) {
          p_log("token found! Name %s\n", token_kind_names[i]);
          cur_token.kind = (token_kind)i;
          break; // exit the loop if a token's been found
        }
      }
    }
    // cur_token.kind = UNKNOWN;
    p_log("current token name is %s\n", token_kind_names[cur_token.kind]);
    if(cur_token.kind == UNKNOWN) { // if the token's unknown
      p_log("token kind unknown");
      if(look_ahead > max_tok_len) { // if the look ahead is greater than max
        s_log("Token still unknown after look ahead %d\n", look_ahead)
        tok_cur += look_ahead+1; // zoom past unknown token shit (miss me w dat)
        look_ahead = 1;
      } else {
        look_ahead++;
      }
    } else { // if the token's kind has been found
      p_log("Token found with ID: %s, val: %d", token_kind_names[cur_token.kind], cur_token.val);
      look_ahead = 0; // reset look ahead
      if(cur_token.kind == NUMBER) { // if it's a number, resolve and look ahead
        cur_token.val = resolve_numb(to_tokenize, tok_cur);
        tok_cur += num_places(cur_token.val); // zoom ahead of the number
      } else {
        tok_cur += strlen(token_kind_names[cur_token.kind]); // zoom ahead of token
      }
      append_token(to_return, cur_token); // append the token
      cur_token.kind = UNKNOWN;
      cur_token.val = 0;
    }
  }
  return to_return;
}

int get_max_tok_len(const char ** to_find_max_len) {
  unsigned int cur_max_len = 0;
  for(unsigned int i = FIRST_TOKEN_KIND; i < LAST_TOKEN_KIND; i++) {
    if(to_find_max_len[i] != NULL) {
      if(strlen(to_find_max_len[i]) > cur_max_len) {
        p_log("Found string %s with token length %d at index %d\n", to_find_max_len[i], strlen(to_find_max_len[i]), i);
        cur_max_len = strlen(to_find_max_len[i]);
      }
    }
  }
  return cur_max_len;
}

// TODO add negative support
int resolve_numb( const char * charstream, int cur ) {
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
  if(to_append_to.toks == NULL || to_append_to.len == 0 || to_append_to.max_len == 0) {
    to_append_to.toks = malloc(sizeof(*to_append_to.toks)*1);
    to_append_to.len = 1;
    to_append_to.max_len = 1;
    return;
  }
  // if the current length is greater or equal to the maximum length
  if( to_append_to.len >= to_append_to.max_len ) {
    // resize the array of tokens to twice its max size
    to_append_to.toks = realloc(to_append_to.toks, to_append_to.max_len*2);
    to_append_to.max_len = to_append_to.max_len*2;
  }
  to_append_to.toks[to_append_to.len] = to_append;
  to_append_to.toks++;
}
