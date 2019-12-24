// PiMien.cpp

#include "PiMien.hpp"
#include "PiCim/PiCim.hpp"
#include "dl/dl.hpp"
#include <cmath>

namespace dl
{
    Image _dl_image;
    Gray _dl_gray;
    Face _dl_face;
    Shape _dl_shape;
    Chip _dl_chip;
    Desc _dl_desc;

    enum
    {
        NONE,
        INIT,
        FACE,
        LANDMARK,
        CHIP,
    } _stage;

} // namespace dl

bool dl_setup()
{
    dl::dlInit();

    return true;
}

bool dl_do_face(void* im)
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    dl::tdl(*cim, dl::_dl_image);

    bool ret = true;
    ret = dl::dlGray(dl::_dl_image, dl::_dl_gray);    if (!ret) return false;
    ret = dl::dlFace(dl::_dl_gray, dl::_dl_face);     if (!ret) return false;

    dl::show(dl::_dl_image, dl::_dl_face);
    dl::fdl(dl::_dl_image, *cim);

    return true;
}

bool dl_do_landmark(void* im)
{
    PiCim::Cim *cim = (PiCim::Cim *)im;

    bool ret = true;
    ret = dl::dlShape(dl::_dl_gray, dl::_dl_face, dl::_dl_shape);   if (!ret) return false;

    dl::show(dl::_dl_image, dl::_dl_shape);
    dl::fdl(dl::_dl_image, *cim);

    return true;
}


bool dl_run_face(void* im, void* face)
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    PiCim::Cface *cface = (PiCim::Cface *)face;
    bool ret = true;
    dl::tdl(*cim, dl::_dl_image);
    ret = dl::dlGray(dl::_dl_image, dl::_dl_gray);    if (!ret) return false;
    ret = dl::dlFace(dl::_dl_gray, dl::_dl_face);     if (!ret) return false;
    dl::fdl(dl::_dl_face, *cface);
    draw_rectangle(dl::_dl_image, dl::_dl_face, rgb_pixel(0xF0, 0x00, 0x00));
    dl::fdl(dl::_dl_image, *cim);

    return true;
}

bool dl_run_landmark(void* im, void* landmark)
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    PiCim::Clandmark *clandmark = (PiCim::Clandmark *)landmark;
    bool ret = true;
    dl::tdl(*cim, dl::_dl_image);
    ret = dl::dlGray(dl::_dl_image, dl::_dl_gray);  if (!ret) return false;
    ret = dl::dlFace(dl::_dl_gray, dl::_dl_face);   if (!ret) return false;
    draw_rectangle(dl::_dl_image, dl::_dl_face, rgb_pixel(0xF0, 0x00, 0x00));
    ret = dl::dlShape(dl::_dl_gray, dl::_dl_face, dl::_dl_shape);   if (!ret) return false;
    dl::fdl(dl::_dl_shape, *clandmark);
    dl::fdl(dl::_dl_image, *cim);

    return true;
}

bool dl_run_chip(void* im, void* chip)
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    PiCim::Cim *cchip = (PiCim::Cim *)chip;
    bool ret = true;
    dl::tdl(*cim, dl::_dl_image);
    ret = dl::dlGray(dl::_dl_image, dl::_dl_gray);  if (!ret) return false;
    ret = dl::dlFace(dl::_dl_gray, dl::_dl_face);   if (!ret) return false;
    ret = dl::dlShape(dl::_dl_gray, dl::_dl_face, dl::_dl_shape); if (!ret) return false;
    ret = dl::dlChip(dl::_dl_image, dl::_dl_shape, dl::_dl_chip);  if (!ret) return false;
    dl::fdl(dl::_dl_chip, *cchip);

    return true;
}

bool dl_run_desc(void* im, void* face, void* landmark, void* chip, void* desc)
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    PiCim::Cface *cface = (PiCim::Cface *)face;
    PiCim::Clandmark *clandmark = (PiCim::Clandmark *)landmark;
    PiCim::Cim *cchip = (PiCim::Cim *)chip;
    bool ret = true;
    dl::tdl(*cim, dl::_dl_image);
    ret = dl::dlGray(dl::_dl_image, dl::_dl_gray);  if (!ret) return false;
    ret = dl::dlFace(dl::_dl_gray, dl::_dl_face);   if (!ret) return false;
    ret = dl::dlShape(dl::_dl_gray, dl::_dl_face, dl::_dl_shape); if (!ret) return false;
    ret = dl::dlChip(dl::_dl_image, dl::_dl_shape, dl::_dl_chip);  if (!ret) return false;
    ret = dl::dlDesc(dl::_dl_chip, dl::_dl_desc);  if (!ret) return false;
    dl::fdl(dl::_dl_face, *cface);
    dl::fdl(dl::_dl_shape, *clandmark);
    dl::fdl(dl::_dl_chip, *cchip);

    dl::show(dl::_dl_image, dl::_dl_face);
    dl::show(dl::_dl_image, dl::_dl_shape);
    dl::fdl(dl::_dl_image, *cim);

    return true;
}
