/* 
 * File:   ocr_regionvalidator.cpp
 * Author: dan
 * 
 * Created on May 25, 2015, 10:37 AM
 */

#include "ocr_regionvalidator.h"

OCR_RegionValidator::OCR_RegionValidator() {
}

OCR_RegionValidator::~OCR_RegionValidator() {
}

int OCR_RegionValidator::getMode()
{
    return iMode;
}

void OCR_RegionValidator::setMode(int __iMode)
{
    iMode = __iMode;
}

void OCR_RegionValidator::setOptional(bool __bOptional)
{
    bOptional = __bOptional;
}

bool OCR_RegionValidator::getOptional()
{
    return bOptional;
}

int OCR_RegionValidator::Validate(std::string szInputString)
{
    int iReturnValue = Passed;
    
    return iReturnValue;
}