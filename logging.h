#ifndef H_LOGGING
#define H_LOGGING
#include "log_config.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef enum log_severity { HIGH, MEDIUM, LOW } log_severity;

// get_log_prefix returns the prefix for a standard log
char *get_log_prefix(int);

// log_fp is the file pointer to the log file
FILE *log_fp;

#ifdef LOG_DEBUG_MODE
// s_log is a standard function to print to stderr and log
#define s_log(fmt, ...)                                                        \
  assert(log_fp != NULL);                                                      \
  char *to_log = strcat(get_log_prefix(strlen(fmt)), fmt);                     \
  to_log = strcat(to_log, "\n");                                               \
  fprintf(log_fp, to_log, ##__VA_ARGS__);                                      \
  fprintf(stderr, to_log, ##__VA_ARGS__);                                      \
  free(to_log);
#else // DEBUG_MODE
#define s_log(...)
#endif // DEBUG_MODE

// Opens and closes log file
void init_logging(const char *log_file_name);
void close_logging();

#endif
