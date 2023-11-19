//doomgeneric for cross-platform development library 'Simple DirectMedia Layer'

#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <stdbool.h>

#include <linux/fb.h>
#include <sys/time.h>
#include <sys/ioctl.h>

int fb_fd = -1;

void DG_Init(){
    fb_fd = open("/dev/fb0", O_RDWR); 

    assert(fb_fd >= 0);

    struct fb_fix_screeninfo fix_screeninfo;
    struct fb_var_screeninfo var_screeninfo;

    assert(ioctl(fb_fd, FBIOGET_FSCREENINFO, &fix_screeninfo) == 0);
    assert(ioctl(fb_fd, FBIOGET_VSCREENINFO, &var_screeninfo) == 0);

    if( 
        fix_screeninfo.visual == FB_VISUAL_TRUECOLOR && 
        var_screeninfo.bits_per_pixel == 32 &&
        var_screeninfo.red.length == 8 && var_screeninfo.red.msb_right == 0 &&
        var_screeninfo.green.length == 8 && var_screeninfo.green.msb_right == 0 &&
        var_screeninfo.blue.length == 8 && var_screeninfo.blue.msb_right == 0 
    ){
        var_screeninfo.xres_virtual = DOOMGENERIC_RESX;
        var_screeninfo.yres_virtual = DOOMGENERIC_RESY;
        assert(ioctl(fb_fd, FBIOPUT_VSCREENINFO, &var_screeninfo) == 0);
    }else{
        perror("'/dev/fb0' : format not supported\n");
        __builtin_unreachable();
    }
}

void DG_DrawFrame(){
    printf("Calling %s\n", __func__);
    write(fb_fd, DG_ScreenBuffer, DOOMGENERIC_RESX * DOOMGENERIC_RESY * sizeof(uint32_t));
}

void DG_SleepMs(uint32_t ms){
    sleep(ms);
}

uint32_t DG_GetTicksMs(){
    struct timeval tv; 
    gettimeofday(&tv, NULL);
    uint32_t milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return milliseconds;
}

int DG_GetKey(int* pressed, unsigned char* doomKey){
    printf("Calling %s\n", __func__);
    return 0;
}

void DG_SetWindowTitle(const char * title){
    printf("Calling %s\n", __func__);
}

int main(int argc, char **argv){
    doomgeneric_Create(argc, argv);

    for(int i = 0; ; i++){
        doomgeneric_Tick();
    }
  
    return 0;
}