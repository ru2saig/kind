#include <gtk/gtk.h>
#include "trayicons.h"
#include "config.h"

// don't really like the following code. refactor after figuring out how to display the icons!
// refactor this in structs? this seems so oop!
#ifdef CAPS_LOCK
#define CAPS_ICON_PATH_ON "/home/ruusaig/Projects/kind/icons/caps_on.svg" // TODO: change these to a compile time variables, which are subsituted during install/make?
#define CAPS_ICON_PATH_OFF "/home/ruusaig/Projects/kind/icons/caps_off.svg" // TODO: change these to a compile time variables, which are subsituted during install/make?

static GtkStatusIcon *caps_lock;
static GdkPixbuf *caps_lock_on, *caps_lock_off;

void toggle_caps_lock(int status)
{
  if(status) {
    gtk_status_icon_set_from_pixbuf(caps_lock, caps_lock_on);
  } else {
    gtk_status_icon_set_from_pixbuf(caps_lock, caps_lock_off);
  }
}
#endif

#ifdef NUM_LOCK
#define NUM_ICON_PATH_ON "/home/ruusaig/Projects/kind/icons/num_on.svg" // or see if gtk provides a way to find them?
#define NUM_ICON_PATH_OFF "/home/ruusaig/Projects/kind/icons/num_off.svg" // or see if gtk provides a way to find them?

static GtkStatusIcon *num_lock;
static GdkPixbuf *num_lock_on, *num_lock_off;

void toggle_num_lock(int status)
{
  if(status) {
    gtk_status_icon_set_from_pixbuf(num_lock, num_lock_on);
  } else {
    gtk_status_icon_set_from_pixbuf(num_lock, num_lock_off);
  }
}

#endif

#ifdef SCROLL_LOCK
#define SCROLL_ICON_PATH_ON "/home/ruusaig/Projects/kind/icons/scroll_on.svg"
#define SCROLL_ICON_PATH_OFF "/home/ruusaig/Projects/kind/icons/scroll_off.svg"

static GtkStatusIcon *scroll_lock;
static GdkPixbuf *scroll_lock_on, *scroll_lock_off;

void toggle_scroll_lock(int status) {
  if(status) {
    gtk_status_icon_set_from_pixbuf(scroll_lock, scroll_lock_on);
  } else {
    gtk_status_icon_set_from_pixbuf(scroll_lock, scroll_lock_off);
  }
}
#endif

void tray_icons_init()
{
  
  // the ordering in which the icons are created seems to order the icons in the systray. wonder if that can be made more to my control?
  #ifdef SCROLL_LOCK
  scroll_lock_on = gdk_pixbuf_new_from_file(SCROLL_ICON_PATH_ON, NULL);
  scroll_lock_off = gdk_pixbuf_new_from_file(SCROLL_ICON_PATH_OFF, NULL);

  scroll_lock = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text (scroll_lock, "Scroll Lock");
  // gtk_status_icon_set_name(scroll_lock, "kind-scroll-lock");
  //gtk_status_icon_set_title(scroll_lock, "kind-scroll-lock");
  gtk_status_icon_set_visible(scroll_lock, 1);
  #endif

  #ifdef NUM_LOCK
  num_lock_on = gdk_pixbuf_new_from_file(NUM_ICON_PATH_ON, NULL);
  num_lock_off = gdk_pixbuf_new_from_file(NUM_ICON_PATH_OFF, NULL);
  
  num_lock = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text(num_lock, "Num Lock");
  //gtk_status_icon_set_name(num_lock, "kind-num-lock");
  //gtk_status_icon_set_title(num_lock, "kind-num-lock");
  gtk_status_icon_set_visible(num_lock, 1);
  #endif 

  #ifdef CAPS_LOCK
  caps_lock_on = gdk_pixbuf_new_from_file(CAPS_ICON_PATH_ON, NULL); // perhaps use the gerror feature?
  caps_lock_off = gdk_pixbuf_new_from_file(CAPS_ICON_PATH_OFF, NULL);

  caps_lock = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text (caps_lock, "Caps Lock");
  //  gtk_status_icon_set_name(caps_lock, "kind-caps-lock");
  //gtk_status_icon_set_title(caps_lock, "kind-caps-lock");
  gtk_status_icon_set_visible(caps_lock, 1);
  #endif
}

void tray_icons_free()
{

  #ifdef CAPS_LOCK
  g_object_unref(caps_lock);
  g_object_unref(caps_lock_on);
  g_object_unref(caps_lock_off);
  #endif

  #ifdef NUM_LOCK
  g_object_unref(num_lock);
  g_object_unref(num_lock_on);
  g_object_unref(num_lock_off);
  #endif

  #ifdef SCROLL_LOCK
  g_object_unref(scroll_lock);
  g_object_unref(scroll_lock_on);
  g_object_unref(scroll_lock_off);
  #endif
  
}

 
