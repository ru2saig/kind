#include <X11/XKBlib.h>
#include <X11/extensions/XKB.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define DEFAULT_DISPLAY (":0")
#define CAPS_LOCK_MASK (0x01)
#define NUM_LOCK_MASK  (0x02)
#define SCRL_LOCK_MASK (0x04)

void usage()
{
  printf("Usage kind []\n"); // how to do options?
  exit(1);
}


#define ICON_PATH_ON "/home/ruusaig/Projects/kind/test.svg"
#define ICON_PATH_OFF "/home/ruusaig/Projects/kind/default16.png"

int main(int argc, char **argv)
{
  
  unsigned int status = 0;
  Display *disp = XOpenDisplay(DEFAULT_DISPLAY); // TODO: add option for user to change disps. how would that work?


  gtk_init(&argc, &argv);

  
  GtkStatusIcon *caps_lock_on = gtk_status_icon_new_from_file(ICON_PATH_ON);
  GtkStatusIcon *caps_lock_off = gtk_status_icon_new_from_file(ICON_PATH_OFF);
  GtkStatusIcon *num_lock_on = gtk_status_icon_new_from_file(ICON_PATH_ON);
  GtkStatusIcon *num_lock_off = gtk_status_icon_new_from_file(ICON_PATH_OFF);

   
  gtk_status_icon_set_tooltip_text (caps_lock_on, "Caps Lock On");
  //gtk_status_icon_set_name (status_icon1, "kindpackage");
  //gtk_status_icon_set_title (status_icon1, "kind");
  gtk_status_icon_set_tooltip_text (caps_lock_off, "Caps Lock Off");
  gtk_status_icon_set_tooltip_text (num_lock_on, "Num Lock On");
  gtk_status_icon_set_tooltip_text (num_lock_off, "Num Lock Off");



  // handle gtk_main_loop withhttps://developer-old.gnome.org/glib/stable/glib-The-Main-Event-Loop.html? register own exits? my main loop func to execute? why this over gtk_main_iterate()?
  /* what to do now: why not just use gtk_main_iteration_do()? with a False?
     1. read up on the main loop
     2. start the loop
     3. be able to end the loop on my own terms. (also run the kbdindicator
function)
     4. stop the loop
     5. clean up
   */

  while(1)
    {
      gtk_main_iteration();
      XkbGetIndicatorState(disp, XkbUseCoreKbd, &status);
  
      // don't really like the following code. refactor after figuring out how to display the icons!
      if(status & CAPS_LOCK_MASK) {
	gtk_status_icon_set_visible (caps_lock_on, TRUE); // any way to make this location dependent? or a way to swap out icon files?
	gtk_status_icon_set_visible (caps_lock_off, FALSE);
	fprintf(stderr, "Caps Lock is ON\n");
      } else {
	gtk_status_icon_set_visible (caps_lock_off, TRUE);
	gtk_status_icon_set_visible (caps_lock_on, FALSE);
	fprintf(stderr, "Caps Lock is OFF\n");
      }

      if(status & NUM_LOCK_MASK) {
	gtk_status_icon_set_visible (num_lock_on, TRUE);
	gtk_status_icon_set_visible (num_lock_off, FALSE);
	fprintf(stderr, "Num Lock is ON\n");
      } else {
	gtk_status_icon_set_visible (num_lock_off, TRUE);
	gtk_status_icon_set_visible (num_lock_on, FALSE);
	fprintf(stderr, "Num Lock is OFF\n");
      }
      /*
      if(status & NUM_LOCK_MASK)
	printf("NumLock is Active\n");
      else
	printf("NumLock is Not Active\n");

      if(status & SCRL_LOCK_MASK)
	printf("Scorll Lock is Active\n");
      else
      printf("Scroll Lock is not Active\n");*/

    }


  //TODO: implement cleanup here
  gtk_main_quit();
  return 0;
}
