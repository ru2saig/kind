#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/XKB.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "trayicons.h"
#include "config.h"


void usage()
{
  printf("Usage kind [OPTIONS]\n\nOPTIONS:\n--quit: stop the kind daemon and clean up\n--default-display: pass the default display you want to use. Defaults to :0\n--help: display this message"); // how to do options?
  exit(0);
}

void quit(int sig)
{
    fprintf(stderr, "stopping and exiting\n");
    gtk_main_quit();
    tray_icons_free();
    exit(0);
}

int main(int argc, char **argv)
{
  unsigned int status = 0;
  Display *disp = XOpenDisplay(DEFAULT_DISPLAY); // TODO: add option for user to change disps. how would that work?
  
  
  gtk_init(&argc, &argv);
  tray_icons_init();
  
  // using a single status variable consumes cpu upto 2.2% with rapid tapping. Maybe a status per indicator will reduce this?
  int old_status = -1; // this makes the loop run at least once
  
  while(1)
    {
      gtk_main_iteration_do(True);
      XkbGetIndicatorState(disp, XkbUseCoreKbd, &status);   

      if(status != old_status) {
	toggle_caps_lock(status & CAPS_LOCK_MASK);
	toggle_num_lock(status & NUM_LOCK_MASK);
	toggle_scroll_lock(status & SCRL_LOCK_MASK);

	old_status = status;
      }
    }
  
  
  quit(0);
  return 0;
}
