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
#include "PiCim/PiCim.hpp"

namespace dl {
	typedef dlib::matrix<dlib::rgb_pixel> Image;
	typedef dlib::matrix<unsigned char> Gray;
	typedef dlib::rectangle Face;
	typedef dlib::full_object_detection Shape;
	typedef dlib::matrix<dlib::rgb_pixel> Chip;
	typedef dlib::matrix<float, 0, 1> Desc;

	typedef struct
	{
		Face face;
		Shape shape;
		Chip chip;
		Desc desc;
	} Feat;
	
    bool dlInit();
    bool dlGray(Image & image, Gray & gray);
    bool dlFace(Gray & gray, Face & face);
    bool dlShape(Gray &gray, Face &face, Shape &shape);
    bool dlChip(Image &image, Shape &shape, Chip &chip);
    bool dlDesc(Chip &chip, Desc &desc);
    
    bool dlFeat(Image &image, Feat &feat);
	void fdl(Image &image, PiCim::Cim &cim);
	void tdl(PiCim::Cim &cim, Image &image);
	void fdl(Face &face, PiCim::Cface &cface);
	void tdl(PiCim::Cface &cface, Face &face);
	void fdl(Shape &shape_dl, PiCim::Clandmark &landmark);

	void show(Image &image, Face &face);
	void show(Image &image, Shape &shape);
} // namespace dl

#endif /* dl_hpp */
