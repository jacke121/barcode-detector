#pragma once
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<string>

class Barcode {
	cv::Mat region;
	std::string text;
	int pageNumber;

public:
	Barcode();
	cv::Mat getBarcode();
	void setBarcode(cv::Mat);
	std::string getText();
	void setText(std::string);
	int getPageNumber();
	void setPageNumber(int);
};
