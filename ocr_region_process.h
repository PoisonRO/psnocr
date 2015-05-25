/* 
 * File:   ocr_region_process.h
 * Author: dan
 *
 * Created on May 25, 2015, 9:43 AM
 */

#ifndef OCR_REGION_PROCESS_H
#define	OCR_REGION_PROCESS_H

#include <string>

class OCR_RegionPostProcess {
    
public:
    
    OCR_RegionPostProcess();
    virtual ~OCR_RegionPostProcess();
    
    int  getOperation();
    void setOperation(int __iOperation);
    std::string processData(std::string szInputString);
    
private:
    
    static const int          opRemoveBlanks    = 1;
    static const int          opToUpperCase     = 2;
    static const int          opToLowerCase     = 3;
    
    int                       iOperation;
};

#endif	/* OCR_REGION_PROCESS_H */

