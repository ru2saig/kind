#include "config.h"
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/XKB.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "trayicons.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


void usage()
{
  printf("Usage kind [OPTIONS]\n\nOPTIONS:\n--quit: stop the kind daemon and clean up\n--default-display: pass the default display you want to use. Defaults to :0\n--help: display this message"); // how to do options?
  exit(0);
}

void quit(int sig)
{
    fprintf(stderr, "stopping and exiting\n");
    // gtk_main_quit();
    tray_icons_free();
    exit(0);
}

int main(int argc, char **argv)
{
  pid_t pid; 
  int ld; // file descriptor of the lock file
  char str[20];
  unsigned int status = 0;
  Display *disp = NULL;

  
  // parsing options
  for(int i = 1; i < argc; i++)
    {
      if(!strcmp(argv[i], "--quit"))
	{
	  ld = open(LOCK_FILE, O_RDWR);
	  if(ld < 0) {
	    fprintf(stderr, "Failed to open lock file. Exiting\n");
	    exit(2);
	  }

	  read(ld, str, 20);
	  kill(atoi(str), SIGTERM);
	  remove(LOCK_FILE);
	  exit(0);
	}
    }

  pid = fork();
  if(pid < 0) {
    fprintf(stderr, "Failed to fork\n");
    exit(3);
  }
  if(pid > 0) exit(0); // parent, so exit 

  // TODO: put the rest of this in a util.h/util.c?
  
  setsid();

  // close all descriptors
  // clear them out as well

  umask(027);

  // making sure only 1 copy is running at a time
  ld = open(LOCK_FILE, O_RDWR | O_CREAT, 0640);
  if(ld < 0) exit(2);
  if(lockf(ld, F_TLOCK, 0) < 0) exit(1);
  sprintf(str, "%d", getpid());
  write(ld, str, strlen(str)); 
  // register handlers
  signal(SIGTERM, quit);
  
  disp = XOpenDisplay(DEFAULT_DISPLAY); // TODO: add option for user to change disps. how would that work?
  gtk_init(&argc, &argv);

  tray_icons_init();
  
  // using a single status variable consumes cpu upto 2.2% with rapid tapping. Maybe a status per indicator will reduce this?
  int old_status = -1; // this makes the loop run at least once
  
  while(1)
    {
      gtk_main_iteration_do(True);
      XkbGetIndicatorState(disp, XkbUseCoreKbd, &status);   

      if(status != old_status) {
	toggle_num_lock(status & NUM_LOCK_MASK);
	toggle_caps_lock(status & CAPS_LOCK_MASK);
	toggle_scroll_lock(status & SCRL_LOCK_MASK);

	old_status = status;
      }
    }
  
  
  quit(0);
  return 0;
}
