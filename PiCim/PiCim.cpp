// ctypes.cpp

#include "PiCim.hpp"

PiCim::Cim _cim;

void PiCim::f_rgb(void *im, uint8_t *pixels, int32_t size_0, int32_t size_1)
{
    Cim *cim = (Cim *)im;
    cim->pixels = pixels;
    cim->size[0] = size_0;
    cim->size[1] = size_1;
    cim->colorfmt = "rgb";
}

void PiCim::t_rgb(void *im, uint8_t *pixels, int32_t *size_0, int32_t *size_1)
{
    Cim *cim = (Cim *)im;
    pixels = cim->pixels;
    *size_0 = cim->size[0];
    *size_1 = cim->size[1];
}

void PiCim::hello()
{
    printf("[PiCim] hello\n");
}

void PiCim::getCim(uint8_t *pixels, int32_t size_0, int32_t size_1)
{
    f_rgb(&_cim, pixels, size_0, size_1);
}

void PiCim::setCim(uint8_t *pixels, int32_t *size_0, int32_t *size_1)
{
    t_rgb(&_cim, pixels, size_0, size_1);
}

void PiCim::get_(int32_t size_0, int32_t size_1)
{

}
