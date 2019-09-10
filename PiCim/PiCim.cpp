// ctypes.cpp

#include "PiCim.hpp"

bool PiCim::f_rgb(void *im, int32_t *size_0, int32_t *size_1, uint8_t *pixels)
{
    Cim *cim = (Cim *)im;
    cim->size[0] = *size_0;
    cim->size[1] = *size_1;
    cim->pixels = pixels;
    cim->colorfmt = "rgb";

    return true;
}
