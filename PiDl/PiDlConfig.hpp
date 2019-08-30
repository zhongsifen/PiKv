#pragma once

#include <string>

namespace PiDl {
	const std::string _M("../dlib_model/");

	const std::string _DAT_SP(_M + "shape_predictor_68_face_landmarks.dat");
	const std::string _DAT_NET(_M + "dlib_face_recognition_resnet_model_v1.dat");
}
