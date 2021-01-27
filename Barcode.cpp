#pragma once
#include "stdafx.h"
#include "Barcode.h"

Barcode::Barcode() {
	this->text = "";
	this->pageNumber = -1;
}

cv::Mat Barcode::getBarcode() {
	return (this->region).clone();
}

void Barcode::setBarcode(cv::Mat reg) {
	this->region = reg.clone();
}

std::string Barcode::getText() {
	return this->text;
}

void Barcode::setText(std::string txt) {
	this->text = txt;
}

int Barcode::getPageNumber() {
	return this->pageNumber;
}

void Barcode::setPageNumber(int pg) {
	this->pageNumber = pg;
}