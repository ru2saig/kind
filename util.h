#ifndef __KIND_UTIL__
#define __KIND_UTIL__

void quit(int); // handles SIG_TERM
void selfdie(); // for use the program to "self die"
void daemonize();
void usage();

#endif
