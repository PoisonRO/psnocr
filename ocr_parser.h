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
#include <libxml++/libxml++.h>
#include "ocr_regionoperation.h"
#include <Magick++.h>

class OCR_Parser {
    
public:
    OCR_Parser();
    
    void load_config(std::string config_file);
    
    virtual ~OCR_Parser();
    void loadImage(std::string image_file);
    
    void process_ocr();
    
private:
    
    std::string                         szPath;
    std::string                         szFileName;
    
    xmlpp::DomParser                    parser;
    std::vector<OCR_RegionOperation*>   regions;
    
    Magick::Image                       pImage;
};

#endif	/* XML_SETTINGS_H */

