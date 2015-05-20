/* 
 * File:   ocr_regionoperation.h
 * Author: dan
 *
 * Created on May 20, 2015, 12:08 PM
 */

#ifndef OCR_REGIONOPERATION_H
#define	OCR_REGIONOPERATION_H

#include <Magick++.h>
#include "ocr_region.h"
#include <string>

class OCR_RegionOperation : public OCR_Region{
    
public:
    
    OCR_RegionOperation() : OCR_Region(){};
    virtual ~OCR_RegionOperation();
    
    void setBaseImage(Magick::Image __pBaseImage);
    void processImage();
    
    void setTempFileName(std::string __szTempFileName);
    
private:
    
    Magick::Image           pBaseImage;

    std::string             szTempFileName;
    
};

#endif	/* OCR_REGIONOPERATION_H */

