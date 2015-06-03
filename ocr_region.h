/* 
 * File:   ocr_region.h
 * Author: dan
 *
 * Created on May 19, 2015, 5:50 PM
 */

#ifndef OCR_REGION_H
#define	OCR_REGION_H

#include <string>

#include "ocr_regionvalidator.h"
#include "ocr_region_process.h"

class OCR_Region {
    
public:
    
    OCR_Region();
    virtual ~OCR_Region();
    void setX1(int __x1);
    void setX2(int __x2);
    void setY1(int __y1);
    void setY2(int __y2);
    void setName(std::string __name);
    std::string getName();
    
    bool checkRegion();
    
    std::string getOCRText();
    
    void addPostProcess(OCR_RegionPostProcess* pp);
    void addValidator(OCR_RegionValidator* validator);
    
protected:
    
    int x1;
    int x2;
    int y1;
    int y2;
    
    std::string name;
    std::string szOCRText;
    
    std::vector<OCR_RegionPostProcess*> pPostProcess;
    std::vector<OCR_RegionValidator*>   pValidators;
    
    void setOCRText(std::string newOCRText);
};

#endif	/* OCR_REGION_H */

