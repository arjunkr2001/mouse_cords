#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <fluidsynth.h>

char *key_name[] = {
    "first",
    "second (or middle)",
    "third",
    "fourth",  // :D
    "fivth"    // :|
};

int main(int argc, char **argv)
{
    Display *display;
    XEvent xevent;
    Window window;

    fluid_settings_t *settings = new_fluid_settings();
    fluid_synth_t *synth = new_fluid_synth(settings);
    fluid_audio_driver_t *adriver = new_fluid_audio_driver(settings, synth);
    fluid_synth_sfload(synth, "./default-GM.sf2", 1);
    fluid_synth_set_gain(synth,2);

    if( (display = XOpenDisplay(NULL)) == NULL )
        return -1;


    window = DefaultRootWindow(display);
    XAllowEvents(display, AsyncBoth, CurrentTime);

    XGrabPointer(display, 
                 window,
                 1, 
                 PointerMotionMask | ButtonPressMask | ButtonReleaseMask , 
                 GrabModeAsync,
                 GrabModeAsync, 
                 None,
                 None,
                 CurrentTime);

    int key;
    int OldRange,OldMax=1919,OldMin=0,NewRange,NewMin=0,NewMax=127,NewValue,OldValue;
    OldRange = (OldMax - OldMin);  
    NewRange = (NewMax - NewMin); 
    while(1) {
        XNextEvent(display, &xevent);

        printf("Mouse X     : %d\n", xevent.xmotion.x_root);
        //key = xevent.xmotion.x_root % 127;
        NewValue = (((xevent.xmotion.x_root - OldMin) * NewRange) / OldRange) + NewMin;
        key = NewValue;
        fluid_synth_noteon(synth, 0, key, 127);
 
        /* Sleep for 1 second */
        usleep(500);
 
        /* Stop the note */
        fluid_synth_noteoff(synth, 0, key);
    }

    return 0;
}