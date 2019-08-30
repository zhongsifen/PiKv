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
#include <dlib/opencv.h>
#include <opencv2/core.hpp>
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
	// void fdl(Face &face_dl, PiCV::Face &face);
	// void fdl(Shape &shape_dl, PiCV::Landmark &landmark);
	// void fdl(Desc &desc_dl, PiCV::Desc &desc);
	
	// void fdl(Feat &feat_dl, PiCV::Feat &feat);

	// void tdl(PiCim::Cim &image, Image &image_d);
	// void tdl(PiCV::Gray &gray, Gray &gray_d);


	// extern "C"
	// {
		// bool setup();
		// bool runFace(PiCim::Cim &frame, PiCV::Face &face);
		// bool runLandmark(PiCim::Cim &frame, PiCV::Landmark &landmark);
		// bool runChip(PiCim::Cim &frame, PiCV::Chip &chip);
		// bool runDesc(PiCim::Cim &frame, PiCV::Desc &desc);

		// bool runFeat(void* image, void* feat);
	// }
}; // namespace PiDl

#endif /* PiDl_hpp */