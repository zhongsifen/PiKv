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

void* cim_create_face()
{
    PiCim::Cface *cface = new PiCim::Cface;
    cface->rect[0] = 42;
    cface->rect[1] = 44;
    cface->rect[2] = 46;
    cface->rect[0] = 42;

    return cface;
}

bool cim_read_face(void* face, int rect[4])
{
    PiCim::Cface *cface = (PiCim::Cface *)face;
    for (int i = 0; i < 4; i++)
    {
        cface->rect[i] = rect[i];
    }

    return true;
}

bool cim_write_face(void *face, int rect[4])
{
    PiCim::Cface *cface = (PiCim::Cface *)face;
    
    printf("write: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d,", cface->rect[i]);
    }
    printf("\n");

    for (int i = 0; i < 4; i++)
    {
        rect[i] = cface->rect[i];
    }

    return true;
}
