#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

#include "logging.h"

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
  POW
} token_kind;

// token_kind_names is an array of the strings in token_kind
const char * token_kind_names[] = {
  [SQUIG] = "~",
  [MULTIPLY] = "*",
  [DIVIDE] = "/",
  [MODULO] = "%",
  [RIGHT_SHIFT] = ">>",
  [LEFT_SHIFT] = "<<",
  [BIN_AND] = "&",
  [ADD] = "+",
  [SUBTRACT] = "-",
  [BIN_OR] = "|",
  [POW] = "^"
};

// ptree_node is a tree of a parse tree
typedef struct ptree_node {
  struct ptree_node * right;
  struct ptree_node * left;
  token_kind tok;
} ptree_node;

const char * parse_expr(char * to_parse) {
  s_log("Parsing expression %s", to_parse);
  return to_parse;
}

int main( int argc, char ** argv ) {
  init_logging(LOG_FILE);
  if( argc < 2 ) {
    s_log("No input from user");
    printf("[first arg] -- string to parse\n");
  } else {
    printf("%s\n", parse_expr(argv[1]));
  }
  close_logging();
}
