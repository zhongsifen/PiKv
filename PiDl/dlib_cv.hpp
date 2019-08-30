//
//  dlib_cv.hpp
//  dlib_cv
//
//  Created by SIFEN ZHONG on 29/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef dlib_cv_hpp
#define dlib_cv_hpp

#include <opencv2/core.hpp>
#include <dlib/opencv.h>
#include <dlib/array2d.h>
#include <dlib/image_processing.h>

#include "PiDl.hpp"

namespace dlib_cv {
	inline
	void fdlib(dlib::point& dlp, cv::Point& cvp) {
		cvp.x = (int)dlp.x();
		cvp.y = (int)dlp.y();
	}
	
	inline
	void fdlib(dlib::dpoint& dlp, cv::Point& cvp) {
		cvp.x = (int)dlp.x();
		cvp.y = (int)dlp.y();
	}

	inline
	void fdlib(dlib::dpoint& dlp, cv::Point2f& cvp) {
		cvp.x = dlp.x();
		cvp.y = dlp.y();
	}
	
	inline
	void fdlib(dlib::point& dlp, cv::Point2f& cvp) {
		cvp.x = dlp.x();
		cvp.y = dlp.y();
	}

	inline
	void fdlib(dlib::rectangle& dlr, cv::Rect& cvr) {
		cvr.x = (int)dlr.left();
		cvr.y = (int)dlr.top();
		cvr.width  = (int)(dlr.right()  - dlr.left() + 1);
		cvr.height = (int)(dlr.bottom() - dlr.top()  + 1);
	}

	inline
	void fdlib(std::vector<dlib::rectangle>& dlrs, std::vector<cv::Rect>& cvrs) {
		int n = (int)dlrs.size();		if (n < 1) return;
		cvrs.resize(n);
		for (int i=0; i<n; ++i) {
			fdlib(dlrs[i], cvrs[i]);
		}
	}

	inline
	void fdlib(dlib::full_object_detection& dlrp, cv::Rect& cvr, std::vector<cv::Point>& cvps) {
		fdlib(dlrp.get_rect(), cvr);
		int n = (int)dlrp.num_parts();		if (n < 1) return;
		cvps.resize(n);
		for (int i = 0; i<n; ++i) {
			fdlib(dlrp.part(i), cvps[i]);
		}
	}


	inline
	void tdlib(cv::Mat& cvimg, dlib::cv_image<dlib::rgb_pixel>& dlimg) {
		dlimg = dlib::cv_image<dlib::rgb_pixel>(cvimg);
	}

	inline
	void tdlib(cv::Mat& cvimg, dlib::cv_image<dlib::bgr_pixel>& dlimg) {
		dlimg = dlib::cv_image<dlib::bgr_pixel>(cvimg);
	}

	inline
	void tdlib(cv::Mat& cvimg, dlib::cv_image < unsigned char > & dlimg) {
		dlimg = dlib::cv_image<unsigned char>(cvimg);
	}

	inline
	void tdlib(cv::Point& cvp, dlib::point& dlp) {
		dlp.x() = cvp.x;
		dlp.y() = cvp.y;
	}

	inline
	void tdlib(cv::Point2f& cvp, dlib::dpoint& dlp) {
		dlp.x() = cvp.x;
		dlp.y() = cvp.y;
	}
	
	inline
	void tdlib(cv::Rect& cvr, dlib::rectangle& dlr) {
		dlr.left() = cvr.x;
		dlr.top()  = cvr.y;
		dlr.right()  = cvr.x + cvr.width  - 1;
		dlr.bottom() = cvr.y + cvr.height - 1;
	}

}

#endif /* dlib_cv_hpp */
