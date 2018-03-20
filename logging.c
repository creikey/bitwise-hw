#include "logging.h"
#include <assert.h>

void init_logging(const char * log_file_name) {
  log_fp = fopen(log_file_name, "a");
  assert(log_fp != NULL);
}

void close_logging() {
  fclose(log_fp);
}
