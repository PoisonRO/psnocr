/* 
 * File:   ocr_regionoperation.cpp
 * Author: dan
 * 
 * Created on May 20, 2015, 12:08 PM
 */

#include "ocr_regionoperation.h"
#include <iostream>

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
}

void OCR_RegionOperation::setTempFileName(std::string __szTempFileName)
{
    szTempFileName = __szTempFileName;
}