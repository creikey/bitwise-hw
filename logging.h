#ifndef H_LOGGING
#define H_LOGGING
#include "log_config.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef enum log_severity { HIGH, MEDIUM, LOW } log_severity;

// get_log_prefix returns the prefix for a standard log
char *get_log_prefix(int size_of_line, int log_line, const char *file_name);
// get_pedantic_log_prefix returns the prefix for a standard log
char *get_pedantic_log_prefix(int size_of_line, int log_line,
                              const char *file_name);
// get_testing_log_prefix returns the prefix for a testing log
char *get_testing_log_prefix(int size_of_line, int log_line,
                             const char *file_name);

// log_fp is the file pointer to the log file
FILE *log_fp;

char *to_log;

#ifdef LOG_DEBUG_MODE
// s_log is a standard function to print to stderr and log
#define s_log(fmt, ...)                                                        \
  assert(log_fp != NULL);                                                      \
  to_log = strcat(get_log_prefix(strlen(fmt), __LINE__, __FILE__), fmt);       \
  to_log = strcat(to_log, "\n");                                               \
  fprintf(log_fp, to_log, ##__VA_ARGS__);                                      \
  fprintf(stderr, to_log, ##__VA_ARGS__);                                      \
  free(to_log);
#else // LOG_DEBUG_MODE
#define s_log(...)
#endif // LOG_DEBUG_MODE

#ifdef LOG_DEBUG_PEDANTIC
// p_log is the same as s_log but pedantic
#define p_log(fmt, ...)                                                        \
  assert(log_fp != NULL);                                                      \
  to_log =                                                                     \
      strcat(get_pedantic_log_prefix(strlen(fmt), __LINE__, __FILE__), fmt);   \
  to_log = strcat(to_log, "\n");                                               \
  fprintf(log_fp, to_log, ##__VA_ARGS__);                                      \
  fprintf(stderr, to_log, ##__VA_ARGS__);                                      \
  free(to_log);
#else // LOG_DEBUG_PEDANTIC
#define p_log(...)
#endif // LOG_DEBUG_PEDANTIC

// t_log is logging a testing error
#define t_log(fmt, ...)                                                        \
  assert(log_fp != NULL);                                                      \
  to_log =                                                                     \
      strcat(get_testing_log_prefix(strlen(fmt), __LINE__, __FILE__), fmt);    \
  to_log = strcat(to_log, "\n");                                               \
  fprintf(log_fp, to_log, ##__VA_ARGS__);                                      \
  fprintf(stderr, to_log, ##__VA_ARGS__);                                      \
  free(to_log);

// Opens and closes log file
void init_logging(const char *log_file_name);
void close_logging();

#endif
