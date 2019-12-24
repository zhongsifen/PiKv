// dl.cpp

#include "dl.hpp"

namespace dl
{
    dlib::frontal_face_detector _fd;
    dlib::shape_predictor _sp;
    dl_anet::anet_type _net;
}

bool dl::dlInit()
{
    _fd = dlib::get_frontal_face_detector();
    dlib::deserialize(_DAT_SP) >> _sp;
    dlib::deserialize(_DAT_NET) >> _net;

    return true;
}

bool dl::dlFeat(Image & image, Feat & feat)
{
    Gray gray;
 
    dlGray(image, gray);
    dlFace(gray, feat.face);
    dlShape(gray, feat.face, feat.shape);
    dlChip(image, feat.shape, feat.chip);
    dlDesc(feat.chip, feat.desc);

    return true;
}

bool dl::dlGray(Image & image, Gray & gray)
{
    dlib::assign_image<Gray, Image>(gray, image);
    return true;
}

bool dl::dlFace(Gray & gray, Face & face)
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

bool dl::dlShape(Gray &gray, Face &face, Shape &shape)
{
    dlib::full_object_detection fo = _sp(gray, face);
    int n = fo.num_parts();     if (n < 1) return false;
    shape = fo;

    return true;
}

bool dl::dlChip(Image &image,  Shape &shape, Chip &chip)
{
    if (shape.num_parts() < 1) return false;
    dlib::extract_image_chip(image, dlib::get_face_chip_details(shape, 150, 0.25), chip);

    return true;
}

bool dl::dlDesc(Chip &chip, Desc &desc)
{
    std::vector<Chip> chips(1, chip);
    std::vector<Desc> descs(1);

    descs = _net(chips);

    desc = descs[0];

    return true;
}


void dl::fdl(Image &image, PiCim::Cim &cim)
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

void dl::tdl(PiCim::Cim &cim, Image &image)
{
    image = Image(cim.size[1], cim.size[0]);
    uint8_t* p = (uint8_t*)&image(0, 0);
    int n = cim.size[0]*cim.size[1]*3;
    for (int k=0; k<n; k++) {
        p[k] = cim.pixels[k];
    }
}

void dl::fdl(Face &face, PiCim::Cface &cface)
{
    cface.rect[0] = (int)face.left();
    cface.rect[1] = (int)face.top();
    cface.rect[2] = (int)face.right();
    cface.rect[3] = (int)face.bottom();
}

void dl::tdl(PiCim::Cface &cface, Face &face)
{
    face = dlib::rectangle(
        cface.rect[0],
        cface.rect[1],
        cface.rect[2],
        cface.rect[3]);
}

void dl::fdl(Shape &shape_dl, PiCim::Clandmark &landmark)
{
    int n = shape_dl.num_parts();
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        landmark.shape[k++] = shape_dl.part(i).x();
        landmark.shape[k++] = shape_dl.part(i).y();
    }
}

// void draw_rectangle(
//     image_type &img,
//     const rectangle &rect,
//     const pixel_type &val,
//     unsigned int thickness = 1);
void dl::show(Image &image, Face &face)
{
    draw_rectangle(image, face, rgb_pixel(0xF0, 0x00, 0x00));
}

// void draw_solid_circle(
//     image_type &img,
//     const dpoint &center_point,
//     double radius,
//     const pixel_type &pixel);
void dl::show(Image &image, Shape &shape)
{
    int n = shape.num_parts();
    for (int i = 0; i < n; i++)
    {
        draw_solid_circle(image, shape.part(i), 1, rgb_pixel(0xF0, 0x00, 0x00));
    }
}
