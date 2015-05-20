/* 
 * File:   ocr_region.cpp
 * Author: dan
 * 
 * Created on May 19, 2015, 5:50 PM
 */

#include "ocr_region.h"

OCR_Region::OCR_Region() 
{
    x1 = -1;
    y1 = -1;
    x2 = -1;
    y2 = -1;
    name = " ";
}

OCR_Region::~OCR_Region() 
{
    
}

void OCR_Region::setX1(int __x1)
{
    x1 = __x1;
}

void OCR_Region::setX2(int __x2)
{
    x2 = __x2;
}

void OCR_Region::setY1(int __y1)
{
    y1 = __y1;
}

void OCR_Region::setY2(int __y2)
{
    y2 = __y2;
}

void OCR_Region::setName(std::string __name)
{
    name = __name;
}
    
bool OCR_Region::checkRegion()
{
    return x1 != -1 && x2 != -1 && y1 != -1 && y2 != -1 && name != " ";
}
