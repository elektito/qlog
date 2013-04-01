#include "qlog.hh"

int main(int argc, char *argv[]) {
  QLOG_DEBUG("some debug information.");
  QLOG_INFO("some information.");
  QLOG_LOGIC("very logical indeed.");
  QLOG_WARNING("your've been warned.");
  QLOG_ERROR("an error. run for your life!");

  return 0;
}
