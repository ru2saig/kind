#ifndef __KIND_CONFIG_H__
#define __KIND_CONFIG_H__

#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#define _DEFAULT_SOURCE // TODO: add the thing like above for this. getdtablesize is the manual page

// where the lock file should is located
//#ifndef LOCK_FILE
#define LOCK_FILE "/tmp/kind.lock"
//#endif

// where kind should look for the tray icons. default this directory
//#ifndef ICON_PREFIX
#define ICON_PREFIX  "/usr/share/kind/icons/"
//#endif

// default display. change here or with --default-display command line option
#define DEFAULT_DISPLAY (":0")

// masks for the keys. it is wise not to fiddle with this
#define CAPS_LOCK_MASK (0x01)
#define NUM_LOCK_MASK  (0x02)
#define SCRL_LOCK_MASK (0x04)

#define CAPS_ICON_PATH_ON "caps_on.svg" // TODO: change these to a compile time variables, which are subsituted during install/make?
#define CAPS_ICON_PATH_OFF "caps_off.svg" // TODO: change these to a compile time variables, which are subsituted during install/make?

#define NUM_ICON_PATH_ON "num_on.svg" // or see if gtk provides a way to find them?
#define NUM_ICON_PATH_OFF "num_off.svg" // or see if gtk provides a way to find them?

#define SCROLL_ICON_PATH_ON "scroll_on.svg"
#define SCROLL_ICON_PATH_OFF "scroll_off.svg"



#endif
