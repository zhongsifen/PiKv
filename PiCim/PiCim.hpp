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
}

extern "C"
{
    // void pic_rgba_rgb(uint8_t pixels_rgba[], uint8_t pixels_rgb[], int size[2]);
    void* cim_get_im();
    void* cim_get_face();
    
    bool cim_open(int size[2], char colorfmt[]);
    bool cim_close();
    bool cim_size(int size[2]);
    bool cim_read_rgb(uint8_t pixels[]);
    bool cim_read_rgba(uint8_t pixels[]);
    bool cim_write_rgb(uint8_t pixels[]);
    
    bool cim_run();

    void* cim_create_face();
    bool cim_read_face(void* cface, int32_t rect[4]);
    bool cim_write_face(void* cface, int32_t rect[4]);
}

#endif
