#ifndef H_NUMBER_TOKEN
#define H_NUMBER_TOKEN

#include "tokens.h"
#include <stdbool.h>

bool is_digit(char to_check);

token parse_number(char *to_parse, int cur, size_t length);

void test_number_token();

#endif // H_NUMBER_TOKEN
