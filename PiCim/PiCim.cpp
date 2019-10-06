// ctypes.cpp

#include "PiCim.hpp"

namespace PiCim
{
    PiCim::Cim _cim;
}

bool PiCim::open_cim(Cim &im, int size[2], uint8_t *pixels, const char *colorfmt)
{
    im.colorfmt = colorfmt;
    im.size[0] = size[0];
    im.size[1] = size[1];
    im.length = (size[0] * size[1]) * ((strcmp(colorfmt, "rgba") == 0) ? 4 : 3);
    im.pixels = (pixels == nullptr) ? new uint8_t[im.length] : pixels;

    return true;
}

bool PiCim::read_cim(Cim &im, uint8_t pixels[])
{
    return true;
}

bool PiCim::write_cim(Cim &im, uint8_t pixels[])
{
    return true;
}

bool PiCim::close_cim(Cim &im)
{
    return true;
}

void PiCim::f_face(void *face, int rect[4])
{

}
void PiCim::t_face(void *face, int rect[4])
{
    Cface *cface = (Cface *)face;
    for (int i=0; i<4; i++) {
        rect[i] = cface->rect[i];
    }
}


void cim_setup(int size[2])
{
    printf("[Cim]setup: before (%d,%d)\n", size[0], size[1]);
    PiCim::open_cim(PiCim::_cim, size);
    printf("[Cim]setup: after (%d,%d)\n", PiCim::_cim.size[0], PiCim::_cim.size[1]);
}

void cim_input_rgb(uint8_t pixels[])
{
    int l = PiCim::_cim.size[0] * PiCim::_cim.size[1];
    uint8_t *p = PiCim::_cim.pixels;
    int i=0, j=0;
    for (int k=0; k<l; k++) {
        p[i++] = pixels[j++];
        p[i++] = pixels[j++];
        p[i++] = pixels[j++];
    }
}

void cim_input_rgba(uint8_t pixels[])
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
}

void cim_get_size(int size[2])
{
    size[0] = PiCim::_cim.size[0];
    size[1] = PiCim::_cim.size[1];
}

void cim_get_rgb(uint8_t pixels[])
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
}

void cim_run()
{
    int n = 256;
}