/* 
 * File:   ocr_region.h
 * Author: dan
 *
 * Created on May 19, 2015, 5:50 PM
 */

#ifndef OCR_REGION_H
#define	OCR_REGION_H

#include <string>

class OCR_Region {
    
public:
    
    OCR_Region();
    virtual ~OCR_Region();
    void setX1(int __x1);
    void setX2(int __x2);
    void setY1(int __y1);
    void setY2(int __y2);
    void setName(std::string __name);
    
    bool checkRegion();
    
protected:
    
    int x1;
    int x2;
    int y1;
    int y2;
    
    std::string name;
    
};

#endif	/* OCR_REGION_H */

