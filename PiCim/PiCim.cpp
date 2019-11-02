// ctypes.cpp

#include "PiCim.hpp"

namespace PiCim
{
    Cim _cim;
    Cface _cface;
}

void *cim_get_im()
{
    return &PiCim::_cim;
}

void* cim_get_face()
{
    return &PiCim::_cface;
}
// void PiCim::f_face(void *face, int rect[4])
// {

// }
// void PiCim::t_face(void *face, int rect[4])
// {
//     Cface *cface = (Cface *)face;
//     for (int i=0; i<4; i++) {
//         rect[i] = cface->rect[i];
//     }
// }

// void pic_rgba_rgb(uint8_t pixels_rgba[], uint8_t pixels_rgb[], int size[2])
// {
//     int l = size[0] * size[1];
//     int i = 0, j = 0;
//     for (int k = 0; k < l; k++)
//     {
//         pixels_rgb[i++] = pixels_rgba[j++];
//         pixels_rgb[i++] = pixels_rgba[j++];
//         pixels_rgb[i++] = pixels_rgba[j++];
//         j++;
//     }
// }

bool cim_open(int size[2], char colorfmt[])
{
    PiCim::_cim.size[0] = size[0];
    PiCim::_cim.size[1] = size[1];
    PiCim::_cim.length = (size[0] * size[1]) * ((strcmp(colorfmt, "rgba") == 0) ? 4 : 3);
    PiCim::_cim.pixels = new uint8_t[PiCim::_cim.length];

    return true;
}

bool cim_close()
{
    PiCim::_cim.size[0] = 0;
    PiCim::_cim.size[1] = 0;
    PiCim::_cim.length = 0;
    delete[] PiCim::_cim.pixels;
    PiCim::_cim.pixels = nullptr;

    return true;
}

bool cim_size(int size[2])
{
    size[0] = PiCim::_cim.size[0];
    size[1] = PiCim::_cim.size[1];

    return true;
}

bool cim_read_rgb(uint8_t pixels[])
{
    int l = PiCim::_cim.size[0] * PiCim::_cim.size[1];
    uint8_t *p = PiCim::_cim.pixels;
    int i=0, j=0;
    for (int k=0; k<l; k++) {
        p[i++] = pixels[j++];
        p[i++] = pixels[j++];
        p[i++] = pixels[j++];
    }

    return true;
}

bool cim_read_rgba(uint8_t pixels[])
{
    int l = PiCim::_cim.size[0] * PiCim::_cim.size[1];
    uint8_t *p = PiCim::_cim.pixels;
    int i = 0, j = 0;
    for (int k = 0; k < l; k++)
    {
        p[i++] = pixels[j++];
        p[i++] = pixels[j++];
        p[i++] = pixels[j++];
        j++;
    }

    return true;
}

bool cim_write_rgb(uint8_t pixels[])
{
    int l = PiCim::_cim.size[0] * PiCim::_cim.size[1];
    uint8_t *p = PiCim::_cim.pixels;
    int i = 0, j = 0;
    for (int k = 0; k < l; k++)
    {
        pixels[j++] = p[i++];
        pixels[j++] = p[i++];
        pixels[j++] = p[i++];
    }

    return true;
}

bool cim_run()
{
    int n = 256;

    return true;
}