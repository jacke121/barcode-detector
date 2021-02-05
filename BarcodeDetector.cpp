#pragma once
#include "stdafx.h"
#include "BarcodeDetector.h"

BarcodeDetector::BarcodeDetector(int w, int h) {
	this->width = w;
	this->height = h;
}

void BarcodeDetector::checkPointBoundary(cv::Point2f& p) {
	if (p.x < 0) {
		p.x = 0;
	}
	if (p.x > 800) {
		p.x = 800;
	}
	if (p.y < 0) {
		p.y = 0;
	}
	if (p.y > 800) {
		p.y = 800;
	}
}

bool BarcodeDetector::compareContourAreas(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2) {
	double i = fabs(contourArea(cv::Mat(contour1)));
	double j = fabs(contourArea(cv::Mat(contour2)));
	return (i < j);
}

void BarcodeDetector::detect(cv::Mat img, cv::Mat& result) {
	// Convert the image to grayscale and resize
	cv::Mat greyMat;
	cv::Size sizImg(width, height);
	cv::cvtColor(img, greyMat, cv::COLOR_BGR2GRAY);
	cv::resize(greyMat, greyMat, sizImg);
	
	// Apply gradient filters across X and Y axes
	int ddepth = CV_32F;
	cv::Mat gradX, gradY;
	Sobel(greyMat, gradX, ddepth, 1, 0, -1);
	Sobel(greyMat, gradY, ddepth, 0, 1, -1);

	// Gradient difference. 
	cv::Mat gradient;
	cv::subtract(gradX, gradY, gradient);
	cv::convertScaleAbs(gradient, gradient);

	// Blur and threshold to remove unwanted regions
	cv::Mat blurr;
	cv::blur(gradient, blurr, cv::Size(9, 9));
	threshold(blurr, blurr, 225, 255, cv::THRESH_BINARY);

	
	// Eorde and dilate regions to remove noise
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(21, 7));
	cv::Mat closed;
	cv::morphologyEx(blurr, closed, cv::MORPH_CLOSE, kernel);
	cv::erode(closed, closed, cv::Mat(), cv::Point(-1, -1), 4);
	cv::dilate(closed, closed, cv::Mat(), cv::Point(-1, -1), 4);

	// Get contours - Basically, the regions of interest
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(closed, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	// std::cout << contours.size() << std::endl;
	std::sort(contours.begin(), contours.end(), compareContourAreas);
	
	// Calculate contour areas
	std::vector<double> allContourAreas(contours.size());
	for (size_t i = 0; i < contours.size(); i++) {
		allContourAreas[i] = fabs(contourArea(cv::Mat(contours[i])));
	}

	// Barcode b = nullptr;
	//cv::Mat result;
	//result.data = nullptr;

	// Barcode areas usually are greater than 2000 - Current threshold, need to do more processing. 
	if (allContourAreas.size() > 0 && *max_element(allContourAreas.begin(), allContourAreas.end()) > 2000) {



		// Extract the contour whose minimum rectangle represenatation has the maximum area
		cv::RotatedRect minRect;
		minRect = minAreaRect(contours[contours.size() - 1]);

		// Bump up the rectangle size by 25%. To make sure the text belonging to barcode is captured
		cv::Size rectSize = minRect.size;
		rectSize.width = rectSize.width + 0.25*rectSize.width;
		rectSize.height = rectSize.height + 0.25*rectSize.height;
		minRect.size = rectSize;

		// Get end points of rectangle containing barcode
		cv::Point2f rect_points[4];
		minRect.points(rect_points);

		// Extract rectangle region containing barcode
		checkPointBoundary(rect_points[1]);
		checkPointBoundary(rect_points[3]);
		cv::Rect rrr(rect_points[1], rect_points[3]);
		result = greyMat(rrr);
		cv::imshow("image2", result);
		cv::waitKey(0);

		// Draw bounding box 
		cv::Mat drawing = img.clone();
		cv::resize(drawing, drawing, sizImg);
		cv::Scalar color = cv::Scalar(0, 255, 0);

		for (int j = 0; j < 4; j++)
		{

			cv::line(drawing, rect_points[j], rect_points[(j + 1) % 4], color);
			//std::cout << rect_points[j] << rect_points[(j + 1) % 4] << std::endl;
		}

		imshow("image2", drawing);
		cv::waitKey(0);
		//return result;
	}
}
