// PiCim.hpp

#ifndef _PiCim_hpp_
#define _PiCim_hpp_

#include <cstdint>
#include <string>

namespace PiCim {
    typedef struct
    {
        int32_t size[2];
        const char *colorfmt;
        uint8_t *pixels;
    } Cim;

    typedef struct
    {
        int32_t rect[4];
    } Cface;
}

extern "C"
{
    // void pic_rgba_rgb(uint8_t pixels_rgba[], uint8_t pixels_rgb[], int size[2]);
    void* cim_get_im();
    void* cim_get_face();
    
    bool cim_open(void* im, int size[2], char *colorfmt);
    bool cim_close(void *im);
    bool cim_get_size(void *im, int size[2]);
    bool cim_read_rgb(void *im, uint8_t pixels[]);
    bool cim_read_rgba(void *im, uint8_t pixels[]);
    bool cim_write_rgb(void *im, uint8_t pixels[]);

    bool cim_run();

    void* cim_create_face();
    bool cim_read_face(void* cface, int32_t rect[4]);
    bool cim_write_face(void* cface, int32_t rect[4]);
}

#endif
