#include <gtk/gtk.h>
#include "trayicons.h"
#include "config.h"

// TODO: figure out what to do when malloc fails.
// the exiting and cleanup procedure, what to do?
// TODO: figure out how to make it more ooc!

static KBDStatusIcon caps_lock;
static KBDStatusIcon num_lock;
static KBDStatusIcon scroll_lock;

void toggle_scroll_lock(int state) { toggle_state(&scroll_lock, state); }
void toggle_num_lock(int state) { toggle_state(&num_lock, state); }
void toggle_caps_lock(int state) { toggle_state(&caps_lock, state); }


void toggle_state(KBDStatusIcon *status_icon, int state)
{
  if(state)
    gtk_status_icon_set_from_pixbuf(status_icon->icon, status_icon->icon_on);   
  else
    gtk_status_icon_set_from_pixbuf(status_icon->icon, status_icon->icon_off);
}


void init_icon(KBDStatusIcon* status_icon, GdkPixbuf* status_icon_on, GdkPixbuf* status_icon_off, const char* tooltip_text, const char* icon_name)
{
  //TODO: better error checking for all of it! and handling!
  status_icon->icon_on = status_icon_on;
  status_icon->icon_off = status_icon_off;

  status_icon->icon = gtk_status_icon_new();
  gtk_status_icon_set_tooltip_text(status_icon->icon, icon_name);
  gtk_status_icon_set_name(status_icon->icon, tooltip_text);
  gtk_status_icon_set_title(status_icon->icon, tooltip_text);
  gtk_status_icon_set_visible(status_icon->icon, 1);

}


void free_icon(KBDStatusIcon* status_icon)
{  
  g_object_unref(status_icon->icon);
  g_object_unref(status_icon->icon_on);
  g_object_unref(status_icon->icon_off);
}
    
void tray_icons_init()
{

  // the ordering in which the icons are created seems to order the icons in the systray. wonder if that can be made more to my control?  
  init_icon(&scroll_lock,
            gdk_pixbuf_new_from_file(ICON_PREFIX SCROLL_ICON_PATH_ON, NULL),
            gdk_pixbuf_new_from_file(ICON_PREFIX SCROLL_ICON_PATH_OFF, NULL),
            "Scroll Lock", "kind-scroll-lock");


  init_icon(&num_lock,
            gdk_pixbuf_new_from_file(ICON_PREFIX NUM_ICON_PATH_ON, NULL),
            gdk_pixbuf_new_from_file(ICON_PREFIX NUM_ICON_PATH_OFF, NULL),
            "Num Lock", "kind-num-lock");


  init_icon(&caps_lock,
            gdk_pixbuf_new_from_file(ICON_PREFIX CAPS_ICON_PATH_ON, NULL),
            gdk_pixbuf_new_from_file(ICON_PREFIX CAPS_ICON_PATH_OFF, NULL),
            "Caps Lock", "kind-caps-lock");
  
}

void tray_icons_free()
{
  free_icon(&scroll_lock);
  free_icon(&num_lock);
  free_icon(&caps_lock);
}
