/* 
 * File:   ocr_region_process.cpp
 * Author: dan
 * 
 * Created on May 25, 2015, 9:43 AM
 */

#include "ocr_region_process.h"

OCR_RegionPostProcess::OCR_RegionPostProcess() {
}

OCR_RegionPostProcess::~OCR_RegionPostProcess() {
}

int  OCR_RegionPostProcess::getOperation()
{
    return iOperation;
}

void OCR_RegionPostProcess::setOperation(int __iOperation)
{
    iOperation = __iOperation;
}

std::string OCR_RegionPostProcess::processData(std::string szInputString) {
    
    std::string newString;
    
    switch (iOperation) {
        case opRemoveBlanks :
            for (std::string::size_type i=0;i<szInputString.size();i++)
                if ( isspace(szInputString[i]) == false )
                    newString.append(std::toupper(szInputString[i]));
            break;
            
        case opToLowerCase:
            for (std::string::size_type i=0;i<szInputString.size();i++)
                newString.append(std::tolower(szInputString[i]));
            break;
            
        case opToUpperCase:
            for (std::string::size_type i=0;i<szInputString.size();i++)
                newString.append(std::toupper(szInputString[i]));
            break;
    }
    
    return newString;
}
