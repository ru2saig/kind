# Kind
Keyboard indicators for your system tray on X11 (for now). This is aimed at laptops and for machines that have a keyboard without keyboard indicator lights.  
Looks kinda like this:  
![image](https://user-images.githubusercontent.com/42857541/154541828-281a466f-1a40-4b89-8f43-8a9c41f35708.png)  


Tested on xfce4-panel 4.16.3.  

## Requirements
- C compiler (c99 support)
- Make
- XLib development headers
- Gtk3 development headers
- git


Get all the required packages command for Debian based systems with this nifty command:
```
sudo apt install libx11-dev libgtk-3-dev build-essential git
```

## Building and Installation
Use ```make``` following for compiling
Use the following for the installation of the binary and icons
```make install``` 
If root user permissions are required, and you've got sudo installed:
```sudo make install```

If using systemd, use ```make install-systemd``` to install and enable the service file.
The service file starts up kind after graphical session is reached, and makes sure kind is stopped.

## Running
Recommended to use systemd service file, but if you still insist, put ```kind &``` into the autostart file, or
add it as one of the startup programs with your DE settings.

## Contributing
I have mad programming skillz, but flaws still seep through microfractures of the facade I put up.
On a serious note, critiques, pull requests welcome! Please be nice, I'm a beginner and still learning, and eager to improve my "mad programming skillz".

## Links, References and other Cool Stuff
https://developer-old.gnome.org/gtk3/stable/GtkStatusIcon.html#gtk-status-icon-new-from-gicon  
https://x.org/releases/current/doc/man/man3/XkbGetIndicatorState.3.xhtml  
https://github.com/osdlyrics/osdlyrics  





