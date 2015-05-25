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
    
    switch (iMode) {
        case opIsNumeric:
            for (std::string::size_type i=0;i<szInputString.size();i++)
                if ( std::isdigit(szInputString[i]) == false) {
                    iReturnValue = NotPassed;
                }
                    
            break;
            
        case opIsDate:
            // TODO
            break;
            
        case opIsString:
            for (std::string::size_type i=0;i<szInputString.size();i++)
                if ( std::isdigit(szInputString[i]) == true) {
                    iReturnValue = NotPassed;
                }
            break;
    }
    
    if (bOptional == true && iReturnValue == NotPassed) {
        iReturnValue = PassedWithErrors;
    }
    
    return iReturnValue;
}