#include "config.h"
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/XKB.h>
#include <gtk/gtk.h>
#include "trayicons.h"
#include "util.h"

int main(int argc, char **argv)
{
  unsigned int status = 0;
  int old_status = -1; // this makes sure it doesn't change every loop
  Display *disp = NULL;
  
  // parsing options
  for(int i = 1; i < argc; i++)
    {
      if(!strcmp(argv[i], "--quit"))
	{
	  selfdie();
	} else if(!strcmp(argv[i], "--help")) {
	usage();
      } else {
	fprintf(stderr, "Invalid option(s)\n");
	usage();
	exit(0);
      }
      
    }

  daemonize(); // daemonize the process
  
  disp = XOpenDisplay(DEFAULT_DISPLAY); // TODO: add option for user to change disps. how would that work?
  gtk_init(&argc, &argv);
  tray_icons_init();

  // using a single status variable consumes cpu upto 2.2% with rapid tapping. Maybe a status per indicator will reduce this?
  
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
  

  
  return 0;
}
