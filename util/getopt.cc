#include "getopt.hh"
#include <string.h>

char *matiec_optarg = NULL;
int matiec_optind = 1;
int matiec_optopt = 0;

int matiec_getopt(int argc, char *const argv[], const char *options) {
  static const char *next = NULL;
  int result = -1;
  matiec_optarg = NULL;

  if (next == NULL || *next == '\0') {
    next = NULL;
    if (matiec_optind < argc && argv[matiec_optind][0] == '-' &&
        argv[matiec_optind][1] != '\0') {
      if (strcmp(argv[matiec_optind], "--") == 0)
        matiec_optind++;
      else
        next = argv[matiec_optind++] + 1;
    }
  }

  if (next != NULL) {
    matiec_optopt = (unsigned char)*next++;
    const char *option = strchr(options, matiec_optopt);
    if (option == NULL || matiec_optopt == ':')
      result = '?';
    else if (option[1] != ':')
      result = matiec_optopt;
    else if (*next != '\0') {
      matiec_optarg = const_cast<char *>(next);
      next = NULL;
      result = matiec_optopt;
    } else if (matiec_optind < argc) {
      matiec_optarg = argv[matiec_optind++];
      next = NULL;
      result = matiec_optopt;
    } else {
      next = NULL;
      result = options[0] == ':' ? ':' : '?';
    }
  }
  return result;
}
