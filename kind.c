#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/XKB.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


#define CAPS_ICON_PATH_ON "/home/ruusaig/Projects/kind/icons/caps_on.svg" // TODO: change these to a compile time variables, which are subsituted during install/make?
#define CAPS_ICON_PATH_OFF "/home/ruusaig/Projects/kind/icons/caps_off.svg" // TODO: change these to a compile time variables, which are subsituted during install/make?
#define NUMS_ICON_PATH_ON "/home/ruusaig/Projects/kind/icons/nums_on.svg" // or see if gtk provides a way to find them?
#define NUMS_ICON_PATH_OFF "/home/ruusaig/Projects/kind/icons/nums_off.svg" // or see if gtk provides a way to find them?
#define SCROLL_ICON_PATH_ON "/home/ruusaig/Projects/kind/icons/scroll_on.svg"
#define SCROLL_ICON_PATH_OFF "/home/ruusaig/Projects/kind/icons/scroll_off.svg"
#define DEFAULT_DISPLAY (":0")
#define CAPS_LOCK_MASK (0x01)
#define NUM_LOCK_MASK  (0x02)
#define SCRL_LOCK_MASK (0x04)
#define LOCK_FILE "/tmp/kind.lock"

void usage()
{
  printf("Usage kind [OPTIONS]\n\nOPTIONS:\n--quit: stop the kind daemon and clean up\n--default-display: pass the default display you want to use. Defaults to :0\n--help: display this message"); // how to do options?
  exit(0);
}

void quit()
{
  exit(0);
}

int main(int argc, char **argv)
{
  unsigned int status = 0;
  Display *disp = XOpenDisplay(DEFAULT_DISPLAY); // TODO: add option for user to change disps. how would that work?
  GdkPixbuf *caps_lock_on, *caps_lock_off, *nums_lock_on, *nums_lock_off, *scroll_lock_on, *scroll_lock_off; // TODO: make an array for each key?
  GtkStatusIcon *caps_lock, *nums_lock, *scroll_lock;
  
  gtk_init(&argc, &argv);

  // conditional inclusion? with the command line options passed!
  caps_lock_on = gdk_pixbuf_new_from_file(CAPS_ICON_PATH_ON, NULL); // perhaps use the gerror feature?
  caps_lock_off = gdk_pixbuf_new_from_file(CAPS_ICON_PATH_OFF, NULL);
  nums_lock_on = gdk_pixbuf_new_from_file(NUMS_ICON_PATH_ON, NULL);
  nums_lock_off = gdk_pixbuf_new_from_file(NUMS_ICON_PATH_OFF, NULL);
  scroll_lock_on = gdk_pixbuf_new_from_file(SCROLL_ICON_PATH_ON, NULL);
  scroll_lock_off = gdk_pixbuf_new_from_file(SCROLL_ICON_PATH_OFF, NULL);
  
  //gtk_status_icon_set_name (status_icon1, "kindpackage"); // what do these do?
  //gtk_status_icon_set_title (status_icon1, "kind");

  scroll_lock = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text (scroll_lock, "Scroll Lock");
  gtk_status_icon_set_visible(scroll_lock, True);
  
  // this will make the num lock icon come first!
  nums_lock = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text(nums_lock, "Num Lock");
  gtk_status_icon_set_visible(nums_lock, True);

  // then this. maybe add patches for this ordering? since command line gets iccky! or an array? a struct?
  caps_lock = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text (caps_lock, "Caps Lock");
  gtk_status_icon_set_visible(caps_lock, True);


  // using a single status variable consumes cpu upto 2.2% with rapid tapping. Maybe a status per indicator will reduce this?
  int old_status = -1; // this makes the loop run at least once
  
  while(1)
    {
      gtk_main_iteration_do(True);
      XkbGetIndicatorState(disp, XkbUseCoreKbd, &status);
      
      // don't really like the following code. refactor after figuring out how to display the icons!
      if(status != old_status) {
	if(status & CAPS_LOCK_MASK) {
	  gtk_status_icon_set_from_pixbuf(caps_lock, caps_lock_on);
	} else {
	  gtk_status_icon_set_from_pixbuf(caps_lock, caps_lock_off);
	}

	if(status & NUM_LOCK_MASK) {
	  gtk_status_icon_set_from_pixbuf(nums_lock, nums_lock_on);
	} else {
	  gtk_status_icon_set_from_pixbuf(nums_lock, nums_lock_off);
	}

	if(status & SCRL_LOCK_MASK) {
	  gtk_status_icon_set_from_pixbuf(scroll_lock, scroll_lock_on);
	} else {
	  gtk_status_icon_set_from_pixbuf(scroll_lock, scroll_lock_off);
	}

	old_status = status;
      }


    }
  

  gtk_main_quit();
  return 0;
}