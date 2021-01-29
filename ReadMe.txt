This project is part of Student Bounty program by Foxit Software.

Goal: Detect barcodes in Foxit PDFs and split the PDFs based on the presence of barcodes in the page.
Use case: Consider a PDF with 10 pages and barcodes on Page 1, 3, 5, 6, 7. The PDF will be split into 5 PDFs with pages 1-2, 3-4, 5, 6, 7-10 respectively.

Steps:
1. Convert the pdf pages into images
2. Barcode detector reads each images
3. Applies image processing operations to determine the potential barcode region
4. Threshold the potential barcode regions to eliminate false positives based on barcode area.
5. Extract the region and save the barcode and corresponding page number it is present in.

Important classes:
1. BarcodeDetector.h, BarcodeDetector.cpp - Takes in an input image and detects barcode in the image if present.
	- Attributes: Resize height and width - This is necessary bacause the image processing filters are 2D matrices applied on the image using a sliding window mechanism. Larger the image resolution, the filters fail to recognize the gradient changes, an important component to detect barcodes.
	- Functions: Detect
	
2. Barcode.h, Barcode.cpp - Store the detected barcode
	- Attributes: Barcode region, text associated with barcode(Need to implement using OCR), page number in which it is present.

Library:
1. OpenCV 4.5.1 - Windows x86 architecture - .lib and .dll files must be generated from source.
2. Foxit Plugin SDK

Constrainints:
1. OpenCV uses filters to process images. Filters are 2D matrix and the size and values must be determined before. There is a need to generalize it for all size of barcodes.
2. Non-horizontal barcodes – A brute-force approach will be to try for every angle between 1 and 90. Runtime is a concern here.

Future Work:
1. Use OCR to parse text within the barcode region. The region usually contains numbers associated with the barcode. This strengthens the elimination of false positives.
2. Generalize for different types of barcodes.

References:
1. https://www.pyimagesearch.com/2014/11/24/detecting-barcodes-images-python-opencv/
2. OpenCV documentation: https://docs.opencv.org/4.5.1/
