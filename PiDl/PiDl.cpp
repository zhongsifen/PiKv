// PiDl.cpp

#include "_PiDl.hpp"
#include "PiCim/PiCim.hpp"
// #include <dlib/image_transforms.h>

namespace PiDl
{
dlib::frontal_face_detector _fd;
dlib::shape_predictor _sp;
dlib_anet::anet_type _net;

Face _dl_face;
Gray _dl_gray;

Image _image;
Shape _shape_dl;
Chip _chip_dl;
Desc _desc_dl;

enum {
	NONE,
	INIT,
	FACE,
	LANDMARK,
	CHIP,
}
_stage;

} // namespace PiDl

bool dl_setup()
{
    PiDl::dlInit();

    return true;
}

bool dl_run_face(void* im, void* face)
{
    bool ret = true;
    PiCim::Cim* cim = (PiCim::Cim*)im;
    PiCim::Cface* cface = (PiCim::Cface*)face;
    PiDl::tdl(*cim, PiDl::_image);
    ret = PiDl::dlGray(PiDl::_image, PiDl::_dl_gray);      if (!ret) return false;
    ret = PiDl::dlFace(PiDl::_dl_gray, PiDl::_dl_face);    if (!ret) return false;
    PiDl::fdl(PiDl::_dl_face, *cface);

    return true;
}

bool dl_show_face(void *im, void *face)
{
    PiCim::Cim *cim = (PiCim::Cim *)im;
    PiCim::Cface *cface = (PiCim::Cface *)face;
    PiDl::Image img;
    PiDl::Face rect;
    rgb_pixel val(0x00, 0x00, 0x00);
    PiDl::tdl(*cim, img);
    PiDl::tdl(*cface, rect);
    draw_rectangle(img, rect, rgb_pixel(0xF0, 0x00, 0x00));
    PiDl::fdl(img, *cim);
    // rgb_pixel val(0x80, 0x80, 0x80);

    return true;
}

#if 0
bool PiDl::runLandmark(PiCim::Cim &frame, PiCV::Landmark &landmark)
{
    bool ret = true;
    tdl(frame, PiDl::_image);
    ret = dlGray(PiDl::_image, PiDl::_dl_gray);  if (!ret) return false;
    ret = dlFace(PiDl::_dl_gray, PiDl::_dl_face);   if (!ret) return false;
    ret = dlShape(PiDl::_dl_gray, PiDl::_dl_face, _shape_dl); if (!ret) return false;
    fdl(_shape_dl, landmark);
 
    return true;
}

bool PiDl::runChip(PiCim::Cim &frame, PiCV::Chip &chip)
{
    bool ret = true;
    tdl(frame, PiDl::_image);
    ret = dlGray(PiDl::_image, PiDl::_dl_gray);  if (!ret) return false;
    ret = dlFace(PiDl::_dl_gray, PiDl::_dl_face);   if (!ret) return false;
    ret = dlShape(PiDl::_dl_gray, PiDl::_dl_face, _shape_dl); if (!ret) return false;
    ret = dlChip(PiDl::_image, _shape_dl, _chip_dl); if (!ret) return false;
    fdl(_chip_dl, chip);

    return true;
}

bool PiDl::runDesc(PiCim::Cim &frame, PiCV::Desc &desc)
{
    bool ret = true;
    tdl(frame, PiDl::_image);
    ret = dlGray(PiDl::_image, PiDl::_dl_gray);  if (!ret) return false;
    ret = dlFace(PiDl::_dl_gray, PiDl::_dl_face);   if (!ret) return false;
    ret = dlShape(PiDl::_dl_gray, PiDl::_dl_face, _shape_dl); if (!ret) return false;
    ret = dlChip(PiDl::_image, _shape_dl, _chip_dl); if (!ret) return false;
    ret = dlDesc(_chip_dl, _desc_dl);
    fdl(_desc_dl, desc);

    return true;
}

bool PiDl::runFeat(void *pPiDl::_image, void *p_feat)
{
    PiCim::Cim *cv_image = (PiCim::Cim*)p_image;
    PiCV::Feat *cv_feat = (PiCV::Feat*)p_feat;
    Image image;
    Feat feat;
    tdl(*cv_image, image);
    dlFeat(image, feat);
    fdl(feat, *cv_feat);

    return true;
}
#endif

bool PiDl::dlInit()
{
    _fd = dlib::get_frontal_face_detector();
    dlib::deserialize(_DAT_SP) >> _sp;
    dlib::deserialize(_DAT_NET) >> _net;
    _stage = INIT;

    return true;
}

bool PiDl::dlFeat(Image & image, Feat & feat)
{
    Gray gray;
 
    dlGray(image, gray);
    dlFace(gray, feat.face);
    dlShape(gray, feat.face, feat.shape);
    dlChip(image, feat.shape, feat.chip);
    dlDesc(feat.chip, feat.desc);

    return true;
}

bool PiDl::dlGray(Image & image, Gray & gray)
{
    dlib::assign_image<Gray, Image>(gray, image);
    return true;
}

bool PiDl::dlFace(Gray & gray, Face & face)
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

bool PiDl::dlShape(Gray &gray, Face &face, Shape &shape)
{
    dlib::full_object_detection fo = _sp(gray, face);
    int n = fo.num_parts();     if (n < 1) return false;
    shape = fo;

    return true;
}

bool PiDl::dlChip(Image &image,  Shape &shape, Chip &chip)
{
    if (shape.num_parts() < 1) return false;
    dlib::extract_image_chip(image, dlib::get_face_chip_details(shape, 150, 0.25), chip);

    return true;
}

bool PiDl::dlDesc(Chip &chip, Desc &desc)
{
    std::vector<Chip> chips(1, chip);
    std::vector<Desc> descs(1);

    descs = _net(chips);

    desc = descs[0];

    return true;
}

#if 0

void PiDl::fdl(Gray &gray_dl, PiCV::Gray &gray)
{
    cv::Mat gray_r(num_rows(gray_dl), num_columns(gray_dl), CV_8UC3, image_data(gray_dl), width_step(gray_dl));
    gray = gray_r.clone();
}

void PiDl::fdl(Shape &shape_dl, PiCV::Landmark &landmark)
{
    int n = shape_dl.num_parts();
    landmark.resize(n);
    for (int i=0; i<n; i++) {
        landmark[i].x = shape_dl.part(i).x();
        landmark[i].y = shape_dl.part(i).y();
    }
}

void PiDl::fdl(Desc &desc_dl, PiCV::Desc &desc)
{
    int n = desc_dl.nr();
    desc.resize(n);
    for (int i=0; i<n; i++) {
        desc[i] = desc_dl(i);
    }
}

void PiDl::fdl(Feat &feat_dl, PiCV::Feat &feat)
{
    fdl(feat_dl.face, feat.face);
    fdl(feat_dl.shape, feat.landmark);
    fdl(feat_dl.chip, feat.chip);
    fdl(feat_dl.desc, feat.desc);
}
#endif

void PiDl::fdl(Image &image, PiCim::Cim &cim)
{
    cim.size[0] = image.nc();
    cim.size[1] = image.nr();
    uint8_t *p = (uint8_t *)&image(0, 0);
    int n = cim.size[0] * cim.size[1] * 3;
    for (int k = 0; k < n; k++)
    {
        cim.pixels[k] = p[k];
    }
}

void PiDl::tdl(PiCim::Cim &cim, Image &image)
{
    image = Image(cim.size[1], cim.size[0]);
    uint8_t* p = (uint8_t*)&image(0, 0);
    int n = cim.size[0]*cim.size[1]*3;
    for (int k=0; k<n; k++) {
        p[k] = cim.pixels[k];
    }
}

// void PiDl::tdl(PiCV::Gray &gray, Gray &gray_dl)
// {
//     dlib::cv_image<dlib::bgr_pixel> graycv_dl(gray);
//     dlib::assign_image(gray_dl, graycv_dl);
// }

void PiDl::fdl(Face &face, PiCim::Cface &cface)
{
    cface.rect[0] = (int)face.left();
    cface.rect[1] = (int)face.top();
    cface.rect[2] = (int)face.right();
    cface.rect[3] = (int)face.bottom();
}

void PiDl::tdl(PiCim::Cface &cface, Face &face)
{
    face = dlib::rectangle(
        cface.rect[0],
        cface.rect[1],
        cface.rect[2],
        cface.rect[3]);
}

// void draw_rectangle(
//     image_type &img,
//     const rectangle &rect,
//     const pixel_type &val,
//     unsigned int thickness = 1);
void PiDl::show_face(PiCim::Cim &cim, PiCim::Cface &cface)
{
    Image img;
    Face rect;
    rgb_pixel val(0x80, 0x80, 0x80);
    tdl(cim, img);
    tdl(cface, rect);
    draw_rectangle(img, rect, val);
}
