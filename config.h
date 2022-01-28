#ifndef __KIND_CONFIG_H__
#define __KIND_CONFIG_H__

#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */



// comment out the icons you don't want
#define CAPS_LOCK 1
#define NUM_LOCK 1
#define SCROLL_LOCK 1

// where the lock file should is located
#define LOCK_FILE "/tmp/kind.lock"

// default display. change here or with --default-display command line option
#define DEFAULT_DISPLAY (":0")

// masks for the keys. it is wise not to fiddle with this
#define CAPS_LOCK_MASK (0x01)
#define NUM_LOCK_MASK  (0x02)
#define SCRL_LOCK_MASK (0x04)



#endif
