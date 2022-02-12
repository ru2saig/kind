#ifndef __TRAY_ICONS_H__
#define __TRAY_ICONS_H__
#include <gtk/gtk.h>

typedef struct kbd_status_icon {
  GtkStatusIcon *icon;
  GdkPixbuf *icon_on, *icon_off;

} KBDStatusIcon;

void toggle_state(KBDStatusIcon*, int);
void init_icon(KBDStatusIcon*, GdkPixbuf*, GdkPixbuf*, const char*, const char*);
void free_icon(KBDStatusIcon*);

void tray_icons_init();
void tray_icons_free();

void toggle_scroll_lock(int);
void toggle_caps_lock(int);
void toggle_num_lock(int);

#endif
