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
        const char *colorfmt;
    } Cim;

    typedef struct
    {
        int32_t rect[4];
    } Cface;

    void f_rgb(void *im, uint8_t *pixels, int32_t size_0, int32_t size_1);
    void t_rgb(void *im, uint8_t *pixels, int32_t *size_0, int32_t *size_1);

    extern "C"
    {
        void hello();
        void getCim(uint8_t *pixels, int32_t size_0, int32_t size_1);
        void setCim(uint8_t *pixels, int32_t *size_0, int32_t *size_1);
        void getCim(uint8_t *pixels, int32_t size_0, int32_t size_1);
    }
}

extern "C"
{
    void cim_setup(uint8_t *pixels, int32_t size_0, int32_t size_1);
    void cim_run();
}

#endif
