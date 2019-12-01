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
    bool cim_open(void* im, int size[2], char *colorfmt);
    bool cim_close(void *im);
    bool cim_get_size(void *im, int size[2]);
    bool cim_read_rgb(void *im, uint8_t pixels[]);
    bool cim_read_rgba(void *im, uint8_t pixels[]);
    bool cim_write_rgb(void *im, uint8_t pixels[]);

    bool cface_read(void* cface, int32_t rect[4]);
    bool cface_write(void* cface, int32_t rect[4]);
}

#endif
