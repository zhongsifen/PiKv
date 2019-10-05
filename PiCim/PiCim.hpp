// PiCim.hpp

#ifndef _PiCim_hpp_
#define _PiCim_hpp_

#include <cstdint>
#include <string>

namespace PiCim {
    typedef struct
    {
        uint8_t *pixels;
        int32_t size[2];
        int32_t length;
        const char *colorfmt;
    } Cim;

    typedef struct
    {
        int32_t rect[4];
    } Cface;

    bool open_cim(Cim &im, int32_t size[2], uint8_t *pixels = nullptr, const char *colorfmt = "rgb");
    bool read_cim(Cim &im, uint8_t pixels[]);
    bool write_cim(Cim &im, uint8_t pixels[]);
    bool close_cim(Cim &im);

    void f_face(void *face, int32_t rect[4]);
    void t_face(void *face, int32_t rect[4]);

}

extern "C"
{
    void cim_size(int size[2]);
    void cim_run();
}

#endif
