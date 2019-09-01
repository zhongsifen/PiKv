// PiCim.hpp

#ifndef _PiCim_hpp_
#define _PiCim_hpp_

#include <cstdint>
#include <string>

namespace PiCim {
    typedef struct
    {
        int32_t size[2];
        uint8_t *pixels;
        char *colorfmt;
    } Cim;

    typedef struct
    {
        int32_t rect[4];
    } Cface;

    bool f_rgb(void* im, int32_t *size_0, int32_t *size_1, uint8_t *pixels);
    bool t_rgb(void *im, int32_t *size_0, int32_t *size_1, uint8_t *pixels);
}

#endif
