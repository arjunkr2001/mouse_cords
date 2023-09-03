#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <fluidsynth.h>

int main(int argc, char** argv)
{
    int fd, bytes;
    //unsigned char data[3];
    int data;

    fluid_settings_t *settings = new_fluid_settings();
    fluid_synth_t *synth = new_fluid_synth(settings);
    fluid_audio_driver_t *adriver = new_fluid_audio_driver(settings, synth);
    fluid_synth_sfload(synth, "./default-GM.sf2", 1);
    fluid_synth_set_gain(synth,2);

    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

    int left, middle, right;
    signed char x, y;
    while(1)
    {
        // Read Mouse     
        bytes = read(fd, &data, sizeof(data));

        // if(bytes > 0)
        // {
        //     left = data[0] & 0x1;
        //     right = data[0] & 0x2;
        //     middle = data[0] & 0x4;

        //     x = data[1];
        //     y = data[2];
        //     printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);
        // } 
        printf("%d\n",data%100); 
        int key = data%100; 
        
        /* Play a note */
        fluid_synth_noteon(synth, 0, key, 127);
 
        /* Sleep for 1 second */
        usleep(500);
 
        /* Stop the note */
        fluid_synth_noteoff(synth, 0, key);
    }
    return 0; 
}
