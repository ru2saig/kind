#include "config.h"
#include "util.h"
#include <unistd.h>
#include "trayicons.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

static char str[20];

void usage()
{
  printf("Usage kind [OPTIONS]\n\nOPTIONS:\n"
         "--quit: stop the kind daemon and clean up\n"
	 "--default-display: [DOES NOT WORK] pass the default display you want to use. Defaults to :0\n"
	 "--help: display this message\n"); 
  exit(0);
}


void quit(int sig)
{
    // gtk_main_quit();
    tray_icons_free();
    remove(LOCK_FILE); // should I put this here? or wherever?
    exit(0);
}

void selfdie()
{
  int ld = open(LOCK_FILE, O_RDWR);
  if(ld < 0) {
    fprintf(stderr, "Failed to open lock file. Exiting\n");
    exit(2);
  }
  
  read(ld, str, 20);
  kill(atoi(str), SIGTERM);
  exit(0);
}
// From: https://web.archive.org/web/20210322223517/www.enderunix.org/docs/eng/daemon.php
void daemonize()
{
  pid_t pid;
  int ld, i;
  
  pid = fork();
  if(pid < 0) {
    fprintf(stderr, "Failed to fork\n");
    exit(3);
  }
  if(pid > 0) exit(0); // parent, so exit 
  
  setsid();
  for (i=getdtablesize();i>=0;--i) close(i); // close all descriptors
  i=open("/dev/null",O_RDWR); dup(i); dup(i); // clear them out as well

  umask(027);

  // making sure only 1 copy is running at a time
  ld = open(LOCK_FILE, O_RDWR | O_CREAT, 0640);
  if(ld < 0) exit(2);
  if(lockf(ld, F_TLOCK, 0) < 0) exit(1);
  sprintf(str, "%d", getpid());
  write(ld, str, strlen(str)); 
  // register handlers
  signal(SIGTERM, quit);
}
