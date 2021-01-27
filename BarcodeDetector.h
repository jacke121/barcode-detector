#pragma once

#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<string>

class BarcodeDetector {
	int width;
	int height;
public:
	BarcodeDetector(int, int);
	void checkPointBoundary(cv::Point2f&);
	void detect(cv::Mat, cv::Mat&);
	static bool compareContourAreas(std::vector<cv::Point>, std::vector<cv::Point>);
};