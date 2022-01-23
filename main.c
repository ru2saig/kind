#include <X11/XKBlib.h>
#include <X11/Xlib.h>
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
  GdkPixbuf *caps_lock_on, *caps_lock_off, *nums_lock_on, *nums_lock_off; // TODO: make an array for each key?
  GtkStatusIcon *caps_lock, *nums_lock;
  
  gtk_init(&argc, &argv);

  caps_lock_on = gdk_pixbuf_new_from_file(ICON_PATH_ON, NULL);
  caps_lock_off = gdk_pixbuf_new_from_file(ICON_PATH_OFF, NULL);
  nums_lock_on = gdk_pixbuf_new_from_file(ICON_PATH_ON, NULL);
  nums_lock_off = gdk_pixbuf_new_from_file(ICON_PATH_OFF, NULL);
  
  //gtk_status_icon_set_name (status_icon1, "kindpackage"); // what do these do?
  //gtk_status_icon_set_title (status_icon1, "kind");


  // this will make the num lock icon come first!
  nums_lock = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text(nums_lock, "Num Lock");
  gtk_status_icon_set_visible(nums_lock, True);

  // then this. maybe add patches for this ordering?
  caps_lock = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text (caps_lock, "Caps Lock");
  gtk_status_icon_set_visible(caps_lock, True);
  
  // nothing at all is 0.0%. very nice (as in no icon)
  // I wonder if, only changing the icon when the status has changed will reduce the load? would that cause a CPU spike? only way to know is to test
  /*      // don't really like the following code. refactor after figuring out how to display the icons!
	  // this implementation takes around 0.7% when switching rapidly enough. takes 1.3% at the most, I've tested
	  if(status != old_status) {
	if(status & CAPS_LOCK_MASK) {
	  gtk_status_icon_set_from_pixbuf(caps_lock, caps_lock_on);
	  fprintf(stderr, "Caps Lock is ON\n");
	} else {
	  gtk_status_icon_set_from_pixbuf(caps_lock, caps_lock_off);
	  fprintf(stderr, "Caps Lock is OFF\n");
	}

	old_status = status;
      }
   */

  
  int old_status = -1; // this makes the loop run at least once
  
  while(1)
    {
      gtk_main_iteration_do(True);
      XkbGetIndicatorState(disp, XkbUseCoreKbd, &status);
      
      // don't really like the following code. refactor after figuring out how to display the icons!
      if(status != old_status) {
	if(status & CAPS_LOCK_MASK) {
	  gtk_status_icon_set_from_pixbuf(caps_lock, caps_lock_on);
	  fprintf(stderr, "Caps Lock is ON\n");
	} else {
	  gtk_status_icon_set_from_pixbuf(caps_lock, caps_lock_off);
	  fprintf(stderr, "Caps Lock is OFF\n");
	}

	if(status & NUM_LOCK_MASK) {
	  gtk_status_icon_set_from_pixbuf(nums_lock, nums_lock_on);
	  fprintf(stderr, "Num Lock is ON\n");
	} else {
	  gtk_status_icon_set_from_pixbuf(nums_lock, nums_lock_off);
	  fprintf(stderr, "Num Lock is OFF\n");
	}

	old_status = status;
      }


    }
  
  //TODO: implement cleanup here
  gtk_main_quit();
  return 0;
}
