// ctypes.cpp

#include "PiCim.hpp"

// namespace PiCim
// {
//     Cim _cim;
//     Cface _cface;
// }

// void *cim_get_im()
// {
//     return &PiCim::_cim;
// }

// void* im_get_face()
// {
//     return &PiCim::_cface;
// }

bool cim_open(void* im, int size[2], char colorfmt[])
{
    PiCim::Cim *cim = (PiCim::Cim*)im;
    cim->size[0] = size[0];
    cim->size[1] = size[1];
    cim->length = (size[0] * size[1]) * ((strcmp(colorfmt, "rgba") == 0) ? 4 : 3);
    cim->pixels = new uint8_t[cim->length];

    return true;
}

bool cim_close(void* im)
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    delete[] cim->pixels;
    cim->size[0] = 0;
    cim->size[1] = 0;
    cim->length = 0;
    cim->pixels = nullptr;

    return true;
}

bool cim_size(void* im, int size[2])
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    size[0] = cim->size[0];
    size[1] = cim->size[1];

    return true;
}

bool cim_read_rgb(void* im, uint8_t pixels[])
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    int l = cim->size[0] * cim->size[1];
    uint8_t *pxs = cim->pixels;
    int i=0, j=0;
    for (int k=0; k<l; k++) {
        pxs[i++] = pixels[j++];
        pxs[i++] = pixels[j++];
        pxs[i++] = pixels[j++];
    }

    return true;
}

bool cim_read_rgba(void *im, uint8_t pixels[])
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    int l = cim->size[0] * cim->size[1];
    uint8_t *pxs = cim->pixels;
    int i = 0, j = 0;
    for (int k = 0; k < l; k++)
    {
        pxs[i++] = pixels[j++];
        pxs[i++] = pixels[j++];
        pxs[i++] = pixels[j++];
        j++;
    }

    return true;
}

bool cim_write_rgb(void *im, uint8_t pixels[])
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    int l = cim->size[0] * cim->size[1];
    uint8_t *pxs = cim->pixels;
    int i = 0, j = 0;
    for (int k = 0; k < l; k++)
    {
        pixels[j++] = pxs[i++];
        pixels[j++] = pxs[i++];
        pixels[j++] = pxs[i++];
    }

    return true;
}

bool cim_run()
{
    int n = 256;

    return true;
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
