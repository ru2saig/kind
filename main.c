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

int main(int argc, char **argv)
{
  unsigned int status = 0;
  Display *disp = XOpenDisplay(DEFAULT_DISPLAY); // TODO: add option for user to change disps. how would that work?
  
  

  while(1)
    {
      XkbGetIndicatorState(disp, XkbUseCoreKbd, &status);

      // don't really like the following code. refactor after figuring out how to display the icons!
      if(status & CAPS_LOCK_MASK)
	printf("CapsLock is Active\n");
      else
	printf("CapsLock is Not Active\n");

      if(status & NUM_LOCK_MASK)
	printf("NumLock is Active\n");
      else
	printf("NumLock is Not Active\n");

      if(status & SCRL_LOCK_MASK)
	printf("Scorll Lock is Active\n");
      else
	printf("Scroll Lock is not Active\n");
      
      
    }



  return 0;
}
