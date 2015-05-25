/* 
 * File:   ocr_regionoperation.cpp
 * Author: dan
 * 
 * Created on May 20, 2015, 12:08 PM
 */

#include "ocr_regionoperation.h"
#include <iostream>

#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

using namespace Magick;

OCR_RegionOperation::~OCR_RegionOperation() {
}

void OCR_RegionOperation::setBaseImage(Magick::Image __pBaseImage)
{
   pBaseImage = __pBaseImage;
}

void OCR_RegionOperation::processImage()
{
    pBaseImage.crop(Geometry(x2-x1,y2-y1,x1,y1));
    pBaseImage.write(szTempFileName);
    processImageOCR();
}

void OCR_RegionOperation::setTempFileName(std::string __szTempFileName)
{
    szTempFileName = __szTempFileName;
}

void OCR_RegionOperation::processImageOCR()
{
    char *outText;
    
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        return;
    }

    // Open input image with leptonica library
    Pix *image = pixRead(szTempFileName.c_str());
    api->SetImage(image);
    
    // Get OCR result
    outText = api->GetUTF8Text();
    std::string OCRText;
    OCRText.append(outText);
    setOCRText(OCRText);
    
    // Destroy used object and release memory
    api->End();
    delete [] outText;
    pixDestroy(&image);
}