/*********************************************************************

 Copyright (C) 2010 Foxit Corporation
 All rights reserved.

 NOTICE: Foxit permits you to use, modify, and distribute this file
 in accordance with the terms of the Foxit license agreement
 accompanying it. If you have received this file from a source other
 than Foxit, then your use, modification, or distribution of it
 requires the prior written permission of Foxit.

 ---------------------------------------------------------------------

Starter.cpp

 - Defines the entry point for the DLL application, the entry point is PlugInMain.

 - Skeleton .cpp file for a plug-in. It implements the basic
   handshaking methods required for all plug-ins.

*********************************************************************/


#include "stdafx.h"
#include "Starter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CStarterApp

BEGIN_MESSAGE_MAP(CStarterApp, CWinApp)
	//{{AFX_MSG_MAP(CStarterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStarterApp construction

CStarterApp::CStarterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStarterApp object

CStarterApp theApp;

/** 
	Starter is a plug-in template that provides a minimal 
	implementation for a plug-in. Developers may use this plug-in a 
	basis for their plug-ins.
*/



/* PIExportHFTs
** ------------------------------------------------------
**/
/** 
** Create and Add the extension HFT's.
**
** @return true to continue loading plug-in,
** false to cause plug-in loading to stop.
*/
FS_BOOL PIExportHFTs(void)
{
	return TRUE;
}

/** 
The application calls this function to allow it to
<ul>
<li> Import HFTs supplied by other plug-ins.
<li> Replace functions in the HFTs you're using (where allowed).
<li> Register to receive notification events.
</ul>
*/
FS_BOOL PIImportReplaceAndRegister(void)
{
	return TRUE;
}

unsigned char* Bitmap2BMP(unsigned char* bitmap, int width, int height, long* len)
{
	int i = 0;
	int j = 0;
	int pitch = width * 3;
	int stride24 = width * 3;
	int stride32 = width * 4;
	if (bitmap == NULL || height == 0 || width == 0)
	{
		return NULL;
	}
	if (pitch % 4 != 0)
	{
		stride24 += 4 - pitch % 4;
	}

	unsigned char* bmpbuf = (unsigned char*)malloc(stride24 * height + 54);
	unsigned char *header = bmpbuf;

	if (NULL == bmpbuf)

		return NULL;

	// write BMP header

	unsigned short bftype;

	unsigned long  bfsize;

	unsigned short bfreserved1;

	unsigned short bfreserved2;

	unsigned long  bfoffbits;


	unsigned long  bisize;

	unsigned long  biwidth;

	unsigned long  biheight;

	unsigned short biplanes;

	unsigned short bibitcount;

	unsigned long  bicompression;

	unsigned long  bisizeimage;

	unsigned long  bixpelspermeter;

	unsigned long  biypelspermeter;

	unsigned long  biclrused;

	unsigned long  biclrimportant;


	bftype = 0x4d42;

	bfsize = stride24 * height + 54;
	bfreserved1 = 0;

	bfreserved2 = 0;

	bfoffbits = 54;


	bisize = 40;

	biwidth = width;

	biheight = height;

	biplanes = 1;

	bibitcount = 24;

	bicompression = 0;

	bisizeimage = stride24 * height;

	bixpelspermeter = 0;

	biypelspermeter = 0;

	biclrused = 0;

	biclrimportant = 0;


	memcpy(bmpbuf, &bftype, 2);
	bmpbuf += 2;

	memcpy(bmpbuf, &bfsize, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &bfreserved1, 2);
	bmpbuf += 2;

	memcpy(bmpbuf, &bfreserved2, 2);
	bmpbuf += 2;

	memcpy(bmpbuf, &bfoffbits, 4);
	bmpbuf += 4;


	memcpy(bmpbuf, &bisize, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &biwidth, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &biheight, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &biplanes, 2);
	bmpbuf += 2;

	memcpy(bmpbuf, &bibitcount, 2);
	bmpbuf += 2;

	memcpy(bmpbuf, &bicompression, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &bisizeimage, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &bixpelspermeter, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &biypelspermeter, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &biclrused, 4);
	bmpbuf += 4;

	memcpy(bmpbuf, &biclrimportant, 4);
	bmpbuf += 4;

	//trans

	for (i = height - 1; i >= 0; i--)
	{
		for (j = 0; j < width; j++)
		{
			bmpbuf[(height - 1 - i)*stride24 + j * 3] = bitmap[i*stride32 + j * 4];
			bmpbuf[(height - 1 - i)*stride24 + j * 3 + 1] = bitmap[i*stride32 + j * 4 + 1];
			bmpbuf[(height - 1 - i)*stride24 + j * 3 + 2] = bitmap[i*stride32 + j * 4 + 2];
		}
	}

	*len = stride24 * height + 54;
	return header;
}

void WriteBMP(FS_DIBitmap  pDIBitmap, const std::string& filename)
{
	FILE* file = fopen(filename.c_str(), "wb");
	if (file == NULL)
		return;

	//Calculate file size
	int nPitch = FSDIBitmapGetPitch(pDIBitmap);
	int nHeight = FSDIBitmapGetHeight(pDIBitmap);
	int nWidth = FSDIBitmapGetWidth(pDIBitmap);
	FS_LPBYTE scan_lines = FSDIBitmapGetBuffer(pDIBitmap);
	int size = 14 + 40 + nPitch * nHeight;

	unsigned char buffer[40];
	//Write file header
	buffer[0] = 'B';
	buffer[1] = 'M';
	buffer[2] = (unsigned char)size;
	buffer[3] = (unsigned char)(size >> 8);
	buffer[4] = (unsigned char)(size >> 16);
	buffer[5] = (unsigned char)(size >> 24);
	buffer[6] = buffer[7] = buffer[8] = buffer[9] = 0;
	buffer[10] = 54;
	buffer[11] = buffer[12] = buffer[13] = 0;
	fwrite(buffer, 14, 1, file);

	//Write bitmap header
	memset(buffer, 0, 40);
	buffer[0] = 40;
	buffer[4] = (unsigned char)nWidth;
	buffer[5] = (unsigned char)(nWidth >> 8);
	buffer[6] = (unsigned char)(nWidth >> 16);
	buffer[7] = (unsigned char)(nWidth >> 24);
	buffer[8] = (unsigned char)(-nHeight);
	buffer[9] = (unsigned char)((-nHeight) >> 8);
	buffer[10] = (unsigned char)((-nHeight) >> 16);
	buffer[11] = (unsigned char)((-nHeight) >> 24);
	buffer[12] = 1;
	buffer[14] = FSDIBitmapGetBPP(pDIBitmap);
	fwrite(buffer, 40, 1, file);

	//Write pixel data
	for (int row = 0; row < nHeight; row++)
	{
		FS_LPBYTE scan_line = scan_lines + row * nPitch;
		fwrite(scan_line, nPitch, 1, file);
	}

	//Finished
	fclose(file);
}


void OnButtonTestProc(void* clientDate)
{
	//FRSysShowMessageBox((FS_LPCWSTR)L"Add your code here.", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	const wchar_t* inputfile = L"";
	FR_Document frDocument;
	CFileDialog dlgFile(TRUE);
	if (dlgFile.DoModal() == IDOK) {
		CString filepath = dlgFile.GetPathName();
		inputfile = filepath.GetString();
		frDocument = FRDocOpenFromFile(inputfile, (FS_LPCSTR)L"", true, true); //shows how to load a PDF and display it
	}
}

void convertActiveDocPagesToImages() {
	// Get the current document
	FR_Document pReaderDoc = FRAppGetActiveDocOfPDDoc();
	if (pReaderDoc == NULL) {
		FRSysShowMessageBox((FS_LPCWSTR)L"Use Select File to load a PDF document before using Detect.", MB_OK, NULL, NULL, FRAppGetMainFrameWnd());
		return;
	}
	FPD_Document fpdDocument = FRDocGetPDDoc(pReaderDoc);
	
	int pagecount = FPDDocGetPageCount(fpdDocument);

	for (int i = 0; i < pagecount; i++)
	{
		FPD_Object pDict = FPDDocGetPage(fpdDocument, i);

		FPD_Page fpdPage = FPDPageNew(); //initialized fpdfPage
		FPDPageLoad(fpdPage, fpdDocument, pDict, TRUE); //Load page into memory
		FPDPageParseContent(fpdPage, NULL); //Parse page data.  Parsing is always required when sorking with FPD_Page

		FPD_RenderOptions renderOptions = FPDRenderOptionsNew();
		if (FPDPageIsParsed(fpdPage))
		{
			FS_FLOAT iWidth = FPDPageGetPageWidth(fpdPage);
			FS_FLOAT iHeight = FPDPageGetPageHeight(fpdPage);

			FS_DIBitmap bitmap = FSDIBitmapNew();
			FSDIBitmapCreate(bitmap, iWidth, iHeight, FS_DIB_Rgb32, NULL, NULL);
			FSDIBitmapClear(bitmap, 0xffffffff);

			FPD_RenderDevice	device = FPDFxgeDeviceNew();
			FPDFxgeDeviceAttach(device, bitmap, 0);

			FPD_RenderContext context = FPDRenderContextNew(fpdPage, 1);

			// display page
			FS_AffineMatrix affineMatrix = FPDPageGetDisplayMatrix(fpdPage, 0, 0, iWidth, iHeight, 0);
			FPDRenderContextAppendPage(context, fpdPage, affineMatrix);

			// display annot 
			FPD_AnnotList annots = FPDAnnotListNew(fpdPage);
			FPDRenderContextAppendPage(context, fpdPage, affineMatrix);
			FPDAnnotListDisplayAnnotsEx(annots, fpdPage, context, FALSE, affineMatrix, TRUE, NULL);


			FPDRenderContextRender(context, device, renderOptions, NULL);

			//SaveBitmap1(L"C:\\aa.bmp", bitmap);
			char  szfile[100] = { 0 };
			sprintf(szfile, "page%d.jpg", i+1);
			WriteBMP(bitmap, szfile);
		}

	}
	//Need to release related resources
}

void detectBarcodesInPageImages()
{
	//cv::Mat image;
	//image = cv::imread("C:\\Users\\Vinay\\Desktop\\cheq.jpeg", cv::IMREAD_COLOR);
	//cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
	//cv::imshow("Display window", image);
	//FRSysShowMessageBox((FS_LPCWSTR)L"Hello World", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());

	//// Load PDF
	//FS_LPCWSTR inputfile = L"C:\\Users\\Vinay\\Desktop\\Foxit\\SCAN-0476.pdf";
	//FR_Document frDocument = FRDocOpenFromFile(inputfile, (FS_LPCSTR)L"", true, true); //shows how to load a PDF and display it

	//// New plugin code
	//FR_Document frDocument1 = FRAppGetActiveDocOfPDDoc(); //Get the active PDF
	//FPD_Document fpdDocument = FRDocGetPDDoc(frDocument1);  //convert the current document type to use by another type
	//int pageCount = FPDDocGetPageCount(fpdDocument);  //get the number of pages.
	//FPD_Object pDict = FPDDocGetPage(fpdDocument, 0);   //Get the first page of the PDF.  Page index starts at 0. pageCount-1 is the last page.  Create a loop based off of pageCount to get other page text.
	//FPD_Page fpdPage = FPDPageNew(); //initialized fpdfPage
	//FPDPageLoad(fpdPage, fpdDocument, pDict, TRUE); //Load page into memory
	//FPDPageParseContent(fpdPage, NULL); //Parse page data.  Parsing is always required when sorking with FPD_Page
	//bool isPageParsed = FPDPageIsParsed(fpdPage); //Checking if parsing has completed successfully.
	//if (!isPageParsed) {
		//FPD_RenderContext context = FPDRenderContextNew(fpdPage, 1);
		//FPD_RenderDevice renderDevice = FPDRenderDeviceNew();
		//FPD_RenderContext renderContext;
		//FS_AffineMatrix affineMatrix = FPDPageGetDisplayMatrix(fpdPage, 0, 0, 24, 24, 0);
		//FPD_RenderOptions renderOptions = FPDRenderOptionsNew();
		//FPDRenderContextDrawPage(context, &renderDevice, fpdPage, &affineMatrix, renderOptions);
		//FS_DIBitmap bitmap = FSDIBitmapNew();
		//FS_FLOAT width = FPDPageGetPageWidth(fpdPage);
		//FS_FLOAT height = FPDPageGetPageHeight(fpdPage);
		//FPDRenderDeviceCreateCompatibleBitmap(renderDevice, &bitmap, width, height);
		//if (bitmap != NULL) {
		//	//void* pBuf = FS_Bitmap_GetBuffer(dib);
		//	FS_LPBYTE pBuf = FSDIBitmapGetBuffer(bitmap);
		//	//get length of bitmap buffer
		//	//int nBufSize = FS_Bitmap_GetStride(dib) * FS_Bitmap_GetHeight(dib);
		//	FS_INT32 nDIBWidth = FSDIBitmapGetHeight(bitmap);
		//	FS_INT32 nDIBHeight = FSDIBitmapGetWidth(bitmap);
		//	//start to output buffer to a bmp
		//	long len;
		//	//create the head of a bmp file
		//	unsigned char* pData = Bitmap2BMP((unsigned char*)pBuf, nDIBHeight, nDIBWidth, &len);
		//	//open file
		//	FILE* pFile = fopen("./test.bmp", "wb");
		//	//write the data of bitmap
		//	fwrite((void*)pData, sizeof(char), len, pFile);
		//	//close file
		//	fclose(pFile);
		//}
	//}

	std::string filePath = "";
	std::string fileName = "";
	int pCount = 9;
	BarcodeDetector bcodeDt(800, 800);
	std::vector<int> pgNos;
	std::vector<Barcode> b;
	for (int i = 1; i <= pCount; i++) {
		std::string full_path = filePath + fileName + "page" + std::to_string(i) + ".jpg";
		std::cout << full_path;
		//"C:\\Users\\Vinay\\Desktop\\Foxit\\Images\\SCAN-0476_Page3.jpg"
		cv::Mat img = cv::imread(full_path);
		cv::Mat barcode;
		bcodeDt.detect(img, barcode);
		if (!barcode.empty()) {
			Barcode tempB;
			tempB.setBarcode(barcode);
			tempB.setPageNumber(i);
			b.push_back(tempB);
			pgNos.push_back(i);
		}
	}
	int iterCount = pgNos.size();
	if (pgNos.size() > 0) {
		pgNos.push_back(pCount + 1);
	}
	int createdPDFIndex = 1;
	for (int i = 0; i < iterCount; i++) {

		FR_Document activeDoc = FRAppGetActiveDocOfPDDoc();
		FPD_Document newFPDDoc = FPDDocNew();  //creates a new document
		FR_Document newFRDoc = FRDocFromPDDoc(newFPDDoc);
		FS_WideString currentpath = FSWideStringNew();
		FRDocGetFilePath(activeDoc, &currentpath);
		FS_StrSize nIndex = FSWideStringGetLength(currentpath);
		FS_WideString wstrOld = FSWideStringNew3((FS_LPCWSTR)L".pdf", wcslen(L".pdf") * sizeof(WCHAR));
		wchar_t newexten[6];
		wsprintf(newexten, L"%i.pdf", createdPDFIndex++); //this is for the file path with incremental numbering.  For example, abc1.pdf, abc2.pdf.
		FS_WideString wstrNew = FSWideStringNew3(newexten, wcslen(newexten) * sizeof(WCHAR));
		FSWideStringReplace(currentpath, wstrOld, wstrNew);
		FS_WordArray warray = FSWordArrayNew();
		for (int j = pgNos[i]; j < pgNos[i + 1]; j++) {
			FSWordArrayAdd(warray, (unsigned short)j - 1);
		}
		// FSWordArrayAdd(warray, (unsigned short)0);
		// FSWordArrayAdd(warray, (unsigned short)1);
		//FRDocExtractPages extracts the section of PDF based off the array (warray) you pass in.  In this case, it is the first two pages.
		if (FRDocExtractPages(activeDoc, warray, newFPDDoc)) {
			int checkPageCount = FPDDocGetPageCount(newFPDDoc);
			FPDDocSave2(newFPDDoc, FSWideStringCastToLPCWSTR(currentpath), FPD_SAVE_DEFAULT, true);
			FSWordArrayRemoveAll(warray);
		}

	}

	if (iterCount > 0)
		FRSysShowMessageBox((FS_LPCWSTR)L"Barcodes detected. PDF split successful.", MB_OK, NULL, NULL, FRAppGetMainFrameWnd());

}



void OnButtonDetectBarcodes(void* clientDate) {

	convertActiveDocPagesToImages();
	detectBarcodesInPageImages();

}

////////////////////////////////////////////////////////////////////
/* Plug-ins can use their Initialization procedures to hook into Foxit Reader's 
	 * user interface by adding menu items, toolbar buttons, windows, and so on.
	 * It is also acceptable to modify Foxit Reader's user interface later when the plug-in is running.
	 */

void PILoadRibbonUI(void* pParentWnd)
{
	FR_RibbonBar fr_Bar = FRAppGetRibbonBar(NULL); //The RibbonBar will free by Foixt Reader or Phantom.
	//FR_RibbonCategory fr_Category = FRRibbonBarAddCategory(fr_Bar, "RibbonCategory", (FS_LPCWSTR)L"RibbonCategory");
	FR_RibbonCategory fr_Category = FRRibbonBarAddCategory(fr_Bar, "Barcode", (FS_LPCWSTR)L"Barcode");
	FR_RibbonPanel fr_Panel = FRRibbonCategoryAddPanel(fr_Category, "Barcode Panel", (FS_LPCWSTR)L"Barcode Panel", NULL);
	FS_INT32 nElementCount = FRRibbonPanelGetElementCount(fr_Panel);
	FR_RibbonButton fr_Button = (FR_RibbonButton)FRRibbonPanelAddElement(fr_Panel, FR_RIBBON_BUTTON, "Select File", (FS_LPCWSTR)L"Select File", nElementCount);
	FR_RibbonElement fr_ElementButton = FRRibbonPanelGetElementByName(fr_Panel, "Select File");
	FRRibbonElementSetTooltip(fr_ElementButton, (FS_LPCWSTR)L"The Ribbon button Tooltip");
	FRRibbonElementSetExecuteProc(fr_ElementButton, OnButtonTestProc);

	// Detect
	FR_RibbonButton fr_ButtonDetect = (FR_RibbonButton)FRRibbonPanelAddElement(fr_Panel, FR_RIBBON_BUTTON,"Detect", (FS_LPCWSTR)L"Detect", nElementCount);
	FR_RibbonElement fr_ElementButtonDetect = FRRibbonPanelGetElementByName(fr_Panel, "Detect");
	FRRibbonElementSetTooltip(fr_ElementButtonDetect, (FS_LPCWSTR)L"The Ribbon button Tooltip");
	FRRibbonElementSetExecuteProc(fr_ElementButtonDetect, OnButtonDetectBarcodes);

}


void PILoadStatusBarUI(void* pParentWnd)
{
	//FRSysShowMessageBox((FS_LPCWSTR)L"PILoadStatusBarUI", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
}

/* PIInit
** ------------------------------------------------------
**/
/** 
	The main initialization routine.
	
	@return true to continue loading the plug-in, 
	false to cause plug-in loading to stop.
*/
FS_BOOL PIInit(void)
{
	return TRUE;
}

/* PIUnload
** ------------------------------------------------------
**/
/** 
	The unload routine.
	Called when your plug-in is being unloaded when the application quits.
	Use this routine to release any system resources you may have
	allocated.

	Returning false will cause an alert to display that unloading failed.
	@return true to indicate the plug-in unloaded.
*/
FS_BOOL PIUnload(void)
{
	return TRUE;
}

/** PIHandshake
	function provides the initial interface between your plug-in and the application.
	This function provides the callback functions to the application that allow it to 
	register the plug-in with the application environment.

	Required Plug-in handshaking routine:
	
	@param handshakeVersion the version this plug-in works with. 
	@param handshakeData OUT the data structure used to provide the primary entry points for the plug-in. These
	entry points are used in registering the plug-in with the application and allowing the plug-in to register for 
	other plug-in services and offer its own.
	@return true to indicate success, false otherwise (the plug-in will not load).
*/
FS_BOOL PIHandshake(FS_INT32 handshakeVersion, void *handshakeData)
{
	if(handshakeVersion != HANDSHAKE_V0100)
		return FALSE;
	
	/* Cast handshakeData to the appropriate type */
	PIHandshakeData_V0100* pData = (PIHandshakeData_V0100*)handshakeData;
	
	/* Set the name we want to go by */
	pData->PIHDRegisterPlugin(pData, "Starter", (FS_LPCWSTR)L"Starter");

	/* If you export your own HFT, do so in here */
	pData->PIHDSetExportHFTsCallback(pData, &PIExportHFTs);
		
	/*
	** If you import plug-in HFTs, replace functionality, and/or want to register for notifications before
	** the user has a chance to do anything, do so in here.
	*/
	pData->PIHDSetImportReplaceAndRegisterCallback(pData, &PIImportReplaceAndRegister);

	/* Perform your plug-in's initialization in here */
	pData->PIHDSetInitDataCallback(pData, &PIInit);

	PIInitUIProcs initUIProcs;
	INIT_CALLBACK_STRUCT(&initUIProcs, sizeof(PIInitUIProcs));
	initUIProcs.lStructSize = sizeof(PIInitUIProcs);
	initUIProcs.PILoadRibbonUI = PILoadRibbonUI;
	initUIProcs.PILoadStatusBarUI = PILoadStatusBarUI;
	pData->PIHDSetInitUICallbacks(pData, &initUIProcs);

	/* Perform any memory freeing or state saving on "quit" in here */
	pData->PIHDSetUnloadCallback(pData, &PIUnload);

	return TRUE;
}

