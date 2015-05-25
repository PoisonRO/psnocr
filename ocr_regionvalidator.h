/* 
 * File:   ocr_regionvalidator.h
 * Author: dan
 *
 * Created on May 25, 2015, 10:37 AM
 */

#ifndef OCR_REGIONVALIDATOR_H
#define	OCR_REGIONVALIDATOR_H

#include <string>

class OCR_RegionValidator {
    
public:
    
    const static int       Passed              =   0;
    const static int       NotPassed           =   1;
    const static int       PassedWithErrors    =   2;  
    
    OCR_RegionValidator();
    virtual ~OCR_RegionValidator();
    
    int         getMode();
    void        setMode(int __iMode);
    void        setOptional(bool __bOptional);
    bool        getOptional();
    
    int         Validate(std::string szInputString);
    
private:

    int                 iMode;
    bool                bOptional;   
    
    const static int    opIsNumeric         =   1;
    const static int    opIsDate            =   2;
    
    // does not contain numbers
    const static int    opIsString          =   3;
    
};

#endif	/* OCR_REGIONVALIDATOR_H */

