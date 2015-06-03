/* 
 * File:   xml_settings.h
 * Author: dan
 *
 * Created on May 19, 2015, 5:20 PM
 */

#ifndef XML_PARSER_H
#define	XML_PARSER_H

#include <string>
#include <vector>
#include "ocr_regionoperation.h"
#include <Magick++.h>
#include <libxml++/libxml++.h>

class OCR_Parser {
    
public:
    
    // stic error codes
    static const    int LOAD_IMAGE_EXCEPTION;
    static const    int LOAD_TEMPLATE_EXCEPTION;
    static const    int PROCESS_OCR_EXCEPTION;
    static const    int IMAGE_NOT_LOADED;
    
    OCR_Parser();
    
    void load_config(std::string config_file) throw(int);
    
    virtual ~OCR_Parser();
    void loadImage(std::string image_file) throw(int);
    
    void process_ocr() throw(int);
    
private:
    
    std::string                         szPath;
    std::string                         szFileName;
    std::string                         szImageFileName;
    
    xmlpp::DomParser                    parser;
    std::vector<OCR_RegionOperation*>   regions;
    
    Magick::Image                       pImage;
    
};

#endif	/* XML_SETTINGS_H */

