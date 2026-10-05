#ifndef MATIEC_GETOPT_HH
#define MATIEC_GETOPT_HH

/* Short-option parser for MSVC, which does not provide POSIX getopt. */
extern char *matiec_optarg;
extern int matiec_optind;
extern int matiec_optopt;
int matiec_getopt(int argc, char *const argv[], const char *options);

#define optarg matiec_optarg
#define optind matiec_optind
#define optopt matiec_optopt
#define getopt matiec_getopt

#endif
