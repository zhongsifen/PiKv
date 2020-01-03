//
//  dl.hpp
//
//  Created by SIFEN ZHONG on 4/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef dl_hpp
#define dl_hpp

#include "dl_config.hpp"
#include "dl_anet.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_transforms.h>

namespace Dl {
	typedef dlib::matrix<dlib::rgb_pixel> Image;
	typedef dlib::matrix<unsigned char> Gray;
	typedef dlib::rectangle Face;
	typedef dlib::full_object_detection Shape;
	typedef dlib::matrix<dlib::rgb_pixel> Chip;
	typedef dlib::matrix<float, 0, 1> Desc;

	typedef enum
    {
        Dl_NONE,
		Dl_INIT,
        Dl_SETUP,
        Dl_FACE,
        Dl_SHAPE,
        Dl_CHIP,
		Dl_DESC,
    } Stage;

	typedef struct
	{
		Image image;
		Gray gray;
		Face face;
		Shape shape;
		Chip chip;
		Desc desc;
		Image view;

		Stage stage;
	} Proc;

	void getImage(Proc& p, Image& image) { image = p.image; }
	void getView(Proc& p, Image& view) { view = p.view; }
	void getChip(Proc& p, Chip& chip) { chip = p.chip; }

	bool init(Proc& p);
	bool setup(Proc& p, Image& image);
	bool reset(Proc& p);
	bool runFace(Proc& p);
	bool runShape(Proc& p);
	bool runChip(Proc& p);
	bool runDesc(Proc& p);
	
    bool dlInit();
    bool dlGray(Image & image, Gray & gray);
    bool dlFace(Gray & gray, Face & face);
    bool dlShape(Gray &gray, Face &face, Shape &shape);
    bool dlChip(Image &image, Shape &shape, Chip &chip);
    bool dlDesc(Chip &chip, Desc &desc);
    
	void showFace(Image &view, Face &face);
	void showShape(Image &view, Shape &shape);
} // namespace Dl

#endif /* dl_hpp */
