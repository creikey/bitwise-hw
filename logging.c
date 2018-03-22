#include "logging.h"
#include <assert.h>
#include <time.h>
#include <malloc.h>

#ifdef LOG_DEBUG_MODE
void init_logging(const char * log_file_name) {
  log_fp = fopen(log_file_name, "a");
  assert(log_fp != NULL);
}

void close_logging() {
  fclose(log_fp);
}
#else // DEBUG_MODE
void init_logging(const char * log_file_name) {
  return;
}
void close_logging() {
  return;
}
#endif // DEBUG_MODE
char * get_log_prefix(int size_of_line) {
  char * to_return = malloc((size_of_line + sizeof(*to_return)) * 100);
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime( &rawtime );
  sprintf(to_return, "[ %s ] ", strtok(asctime(timeinfo), "\n"));
  return to_return;
}
