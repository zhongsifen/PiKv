// PiMien.cpp

#include "PiMien.hpp"
#include "dl/dl.hpp"
// #include <cmath>

namespace Mien {
    Dl::Proc _p;

    typedef struct
    {
        int32_t size[2];
        uint8_t *pixels;
    } Cim;

    typedef struct
    {
        float desc[128];
    } Cdesc;

	void fdl(Dl::Image &image, Cim &cim);
	void tdl(Cim &cim, Dl::Image &image);
    void fdl(Dl::Desc &desc, Cdesc &cdesc);
	// void fdl(Dl::Face &face, PiCim::Cface &cface);
	// void tdl(PiCim::Cface &cface, Dl::Face &face);
	// void fdl(Dl::Shape &shape_dl, PiCim::Clandmark &landmark);
}

void Mien::fdl(Dl::Image &image, Mien::Cim &cim)
{
    cim.size[0] = image.nc();
    cim.size[1] = image.nr();
    int n = cim.size[0] * cim.size[1] * 3;
    uint8_t *p = (uint8_t *)&image(0, 0);
    for (int k = 0; k < n; k++)
    {
        cim.pixels[k] = p[k];
    }
}

void Mien::tdl(Mien::Cim &cim, Dl::Image &image)
{
    image = Dl::Image(cim.size[1], cim.size[0]);
    uint8_t* p = (uint8_t*)&image(0, 0);
    int n = cim.size[0]*cim.size[1]*3;
    for (int k=0; k<n; k++) {
        p[k] = cim.pixels[k];
    }
}

void Mien::fdl(Dl::Desc &desc, Mien::Cdesc &cdesc)
{
    for (int k=0; k<128; k++) {
        cdesc.desc[k] = desc(k);
    }
}

#if 0
void fdl(Face &face, PiCim::Cface &cface)
{
    cface.rect[0] = (int)face.left();
    cface.rect[1] = (int)face.top();
    cface.rect[2] = (int)face.right();
    cface.rect[3] = (int)face.bottom();
}

void tdl(PiCim::Cface &cface, Face &face)
{
    face = dlib::rectangle(
        cface.rect[0],
        cface.rect[1],
        cface.rect[2],
        cface.rect[3]);
}

void fdl(Shape &shape_dl, PiCim::Clandmark &landmark)
{
    int n = shape_dl.num_parts();
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        landmark.shape[k++] = shape_dl.part(i).x();
        landmark.shape[k++] = shape_dl.part(i).y();
    }
}
#endif

bool cim_setup(void* im, int size[2])
{
    Mien::Cim *cim = (Mien::Cim*)im;
    cim->size[0] = size[0];
    cim->size[1] = size[1];
    cim->pixels = new uint8_t[(size[0] * size[1]) * 3];

    return true;
}

bool cim_close(void* im)
{
    Mien::Cim *cim = (Mien::Cim *)im;
    delete[] cim->pixels;
    cim->size[0] = 0;
    cim->size[1] = 0;
    cim->pixels = nullptr;

    return true;
}

bool cim_get_size(void* im, int size[2])
{
    Mien::Cim *cim = (Mien::Cim *)im;
    size[0] = cim->size[0];
    size[1] = cim->size[1];

    return true;
}

bool cim_read_rgb(void* im, uint8_t pixels[])
{
    Mien::Cim *cim = (Mien::Cim *)im;
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

bool cim_read_rgba(void* im, uint8_t pixels[])
{
    Mien::Cim *cim = (Mien::Cim *)im;
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

bool cim_write_rgb(void* im, uint8_t pixels[])
{
    Mien::Cim *cim = (Mien::Cim *)im;
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

bool cdesc_write(void* desc, float d[])
{
    Mien::Cdesc *cdesc = (Mien::Cdesc *)desc;
    for (int k = 0; k < 128; k++)
    {
        d[k] = cdesc->desc[k];
    }

    return true;
}

bool cdesc_read(void* desc, float d[])
{
    Mien::Cdesc *cdesc = (Mien::Cdesc *)desc;
    for (int k = 0; k < 128; k++)
    {
        cdesc->desc[k] = d[k];
    }

    return true;
}

bool mien_init()
{
    bool ret = true;
    ret = Dl::init(Mien::_p);   if (!ret) return false;

    return true;
}

bool mien_setup(void* im, void* view)
{
    bool ret = true;
    Mien::Cim *cim = (Mien::Cim *)im;
    Mien::Cim *cview = (Mien::Cim *)view;
    Mien::tdl(*cim, Mien::_p.image);
    ret = Dl::setup(Mien::_p, Mien::_p.image);    if (!ret) return false;
    Mien::fdl(Mien::_p.image, *cview);

    return true;
}

bool mien_run_face(void* view)
{
    Mien::Cim *cview = (Mien::Cim *)view;
    bool ret = true;
    ret = Dl::runFace(Mien::_p);    if (!ret) return false;
    Mien::fdl(Mien::_p.view, *cview);

    return true;
}

bool mien_run_chip(void* chip, void* view)
{
    Mien::Cim *cchip = (Mien::Cim *)chip;
    Mien::Cim *cview = (Mien::Cim *)view;
    bool ret = true;
    ret = Dl::runShape(Mien::_p);   if (!ret) return false;
    ret = Dl::runChip(Mien::_p);    if (!ret) return false;
    Mien::fdl(Mien::_p.chip, *cchip);
    Mien::fdl(Mien::_p.view, *cview);

    return true;
}

bool mien_run_desc()
{
    bool ret = true;
    ret = Dl::runDesc(Mien::_p);    if (!ret) return false;

    return true;
}

bool mien_run(void* desc, void* chip, void* view)
{
    Mien::Cdesc *cdesc = (Mien::Cdesc *)desc;
    Mien::Cim *cchip = (Mien::Cim *)chip;
    Mien::Cim *cview = (Mien::Cim *)view;
    bool ret = true;
    ret = Dl::runShape(Mien::_p);   if (!ret) return false;
    ret = Dl::runChip(Mien::_p);    if (!ret) return false;
    ret = Dl::runDesc(Mien::_p);    if (!ret) return false;
    Mien::fdl(Mien::_p.desc, *cdesc);
    Mien::fdl(Mien::_p.chip, *cchip);
    Mien::fdl(Mien::_p.view, *cview);

    return true;
}
