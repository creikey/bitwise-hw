#ifndef H_TESTING
#define H_TESTING

#include <stdbool.h>

const char *_t_suit_name;
const char *_t_name;
bool _t_failed;
unsigned int _t_failures;

// t_init starts testing
void t_init();

// t_start_suit starts a suit of tests
void t_start_suit(const char *to_change_to);

// t_end_suit ends the current Suite
void t_end_suit();

// t_start_test starts a test
void t_start_test(const char *test_name);

// t_end_test ends a test
void t_end_test();

void _t_assert(bool expr, int line_numb, const char *file,
               const char *expr_text);

// T_ASSERT asserts that an expr is true
#define T_ASSERT(x) _t_assert(x, __LINE__, __FILE__, #x)

// t_end ends testing
void t_end();

#endif
