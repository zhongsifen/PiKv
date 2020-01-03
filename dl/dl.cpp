// dl.cpp

#include "dl.hpp"

namespace Dl
{
    dlib::frontal_face_detector _fd;
    dlib::shape_predictor _sp;
    dl_anet::anet_type _net;
}

bool Dl::dlInit()
{
    _fd = dlib::get_frontal_face_detector();
    dlib::deserialize(_DAT_SP) >> _sp;
    dlib::deserialize(_DAT_NET) >> _net;

    return true;
}

// bool Dl::dlFeat(Image & image, Feat & feat)
// {
//     Gray gray;
 
//     dlGray(image, gray);
//     dlFace(gray, feat.face);
//     dlShape(gray, feat.face, feat.shape);
//     dlChip(image, feat.shape, feat.chip);
//     dlDesc(feat.chip, feat.desc);

//     return true;
// }

bool Dl::dlGray(Image & image, Gray & gray)
{
    dlib::assign_image<Gray, Image>(gray, image);
    return true;
}

bool Dl::dlFace(Gray & gray, Face & face)
{
    std::vector<std::pair<double, dlib::rectangle>> dets;
    _fd(gray, dets);

    int n = (int)dets.size();   if (n < 1) return false;
    int i = 0;
    double p = dets[0].first;
    for (int k = 1; k < n; k++)
    {
        double q = dets[k].first;
        if (p < q)
        {
            p = q;
            i = k;
        }
    }
    face = dets[i].second;

    return true;
}

bool Dl::dlShape(Gray &gray, Face &face, Shape &shape)
{
    dlib::full_object_detection fo = _sp(gray, face);
    int n = fo.num_parts();     if (n < 1) return false;
    shape = fo;

    return true;
}

bool Dl::dlChip(Image &image,  Shape &shape, Chip &chip)
{
    if (shape.num_parts() < 1) return false;
    dlib::extract_image_chip(image, dlib::get_face_chip_details(shape, 150, 0.25), chip);

    return true;
}

bool Dl::dlDesc(Chip &chip, Desc &desc)
{
    std::vector<Chip> chips(1, chip);
    std::vector<Desc> descs(1);
    descs = _net(chips);
    desc = descs[0];

    return true;
}


// void draw_rectangle(
//     image_type &img,
//     const rectangle &rect,
//     const pixel_type &val,
//     unsigned int thickness = 1);
void Dl::showFace(Image &view, Face &face)
{
    draw_rectangle(view, face, rgb_pixel(0xF0, 0x00, 0x00));
}

// void draw_solid_circle(
//     image_type &img,
//     const dpoint &center_point,
//     double radius,
//     const pixel_type &pixel);
void Dl::showShape(Image &view, Shape &shape)
{
    int n = shape.num_parts();
    for (int i = 0; i < n; i++)
    {
        draw_solid_circle(view, shape.part(i), 2, rgb_pixel(0xF0, 0x00, 0x00));
    }
}

bool Dl::init(Proc& p)
{
    dlInit();
    p.stage = Dl_INIT;

    return true;
}

bool Dl::setup(Proc& p, Image& image)
{
    assert(p.stage >= Dl_INIT);
    p.image = image;
    p.view = p.image;
    // assign_image(p.view, p.image);
    p.stage = Dl_SETUP;

    return true;
}

bool Dl::reset(Proc& p)
{
    assert(p.stage >= Dl_SETUP);
    assign_image(p.view, p.image);

    return true;
}

bool Dl::runFace(Proc& p)
{
    assert(p.stage >= Dl_SETUP);
    dlGray(p.image, p.gray);
    dlFace(p.gray, p.face);
    showFace(p.view, p.face);
    p.stage = Dl_FACE;

    return true;
}

bool Dl::runShape(Proc& p)
{
    assert(p.stage >= Dl_FACE);
    dlShape(p.gray, p.face, p.shape);
    showShape(p.view, p.shape);
    p.stage = Dl_SHAPE;

    return true;
}

bool Dl::runChip(Proc& p)
{
    assert(p.stage >= Dl_SHAPE);
    dlChip(p.image, p.shape, p.chip);
    p.stage = Dl_CHIP;

    return true;
}

bool Dl::runDesc(Proc& p)
{
    assert(p.stage >= Dl_CHIP);
    dlDesc(p.chip, p.desc);
    p.stage = Dl_DESC;

    return true;
}