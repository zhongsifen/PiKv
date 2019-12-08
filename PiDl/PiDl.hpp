//
//  PiDl.hpp
//  PiDl
//
//  Created by SIFEN ZHONG on 4/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef PiDl_hpp
#define PiDl_hpp

#include "PiDlConfig.hpp"
#include "dlib_anet.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_transforms.h>
#include "PiCim/PiCim.hpp"

namespace PiDl {
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

	// void fdl(Image & image_d, PiCim::Cim & image);
	// void fdl(Gray &gray_d, PiCV::Gray &gray);
	// void fdl(Shape &shape_dl, PiCV::Landmark &landmark);
	// void fdl(Desc &desc_dl, PiCV::Desc &desc);
	
	void fdl(Image &image, PiCim::Cim &cim);
	void tdl(PiCim::Cim &cim, Image &image);
	void fdl(Face &face, PiCim::Cface &cface);
	void tdl(PiCim::Cface &cface, Face &face);
	void fdl(Shape &shape_dl, PiCim::Clandmark &landmark);

	void show_face(PiCim::Cim &cim, PiCim::Cface &cface);

} // namespace PiDl

extern "C"
{
	bool dl_setup();
	bool dl_run_face(void* im, void* face);
	bool dl_show_face(void* im, void* face);
	bool dl_run_landmark(void* im, void* landmark);
	// bool runChip(PiCim::Cim &frame, PiDl::Chip &chip);
	// bool runDesc(PiCim::Cim &frame, PiDl::Desc &desc);

	// bool runFeat(void* image, void* feat);
}

#endif /* PiDl_hpp */
