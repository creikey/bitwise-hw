#ifndef H_LOGGING
#define H_LOGGING

#include <stdio.h>

// log_fp is the file pointer to the log file
FILE *log_fp;
// s_log is a standard function to print to stderr and log
#define s_log(...)                                                             \
  assert(log_fp != NULL);                                                      \
  fprintf(stderr, __VA_ARGS__);                                                \
  fprintf(log_fp, __VA_ARGS__)

// Opens and closes log file
void init_logging(const char *log_file_name);
void close_logging();

#endif
