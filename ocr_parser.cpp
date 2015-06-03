/* 
 * File:   xml_settings.cpp
 * Author: dan
 * 
 * Created on May 19, 2015, 5:20 PM
 */

#include "ocr_parser.h"
#include "ocr_region_process.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <libxml++/attribute.h>
#include <exception>
//https://developer.gnome.org/libxml++-tutorial/stable/chapter-parsers.html

using namespace Magick;

// <editor-fold desc="Static variables" defaultstate="collapsed">
const  int OCR_Parser::LOAD_IMAGE_EXCEPTION                     = 1;
const  int OCR_Parser::LOAD_TEMPLATE_EXCEPTION                  = 2;
const  int OCR_Parser::PROCESS_OCR_EXCEPTION                    = 3;
const  int OCR_Parser::IMAGE_NOT_LOADED                         = 4;
// </editor-fold>

OCR_Parser::OCR_Parser() {
    szImageFileName=" ";
}

OCR_Parser::~OCR_Parser() {
    
    OCR_RegionOperation *region;
    
    for (int i = 0;i<regions.size();i++)
    {
        region = regions[i];
        delete region;
        region = NULL;
    }
}

void OCR_Parser::load_config(std::string config_file)  throw(int)
{
    
    if (szImageFileName == " ") throw IMAGE_NOT_LOADED;
    
    // get file name and path
    
    try {
    
        std::string delimiter = "/";
        size_t last;

        last = config_file.find_last_of(delimiter);

        szPath.assign(config_file,0,last);
        szFileName.assign(config_file,last+1,config_file.size()-last);

        parser.parse_file(config_file);

        if (!parser) return;

        xmlpp::Node* pMainNode = parser.get_document()->get_root_node();

        //get only region children
        xmlpp::Node::NodeList pRegions = pMainNode->get_children("region");

        xmlpp::Node::NodeList pRegionProperties;
        xmlpp::Node* pCurrentRegionNode = NULL;
        xmlpp::Element *pCurrentRegionElement = NULL;
        xmlpp::Attribute *pCurrentRegionAttribute = NULL;

        xmlpp::Node* pCurrentRegionPropNode = NULL;
        xmlpp::Element *pCurrentRegionPropElement = NULL;
        xmlpp::Attribute *pCurrentRegionPropAttribute = NULL;

        OCR_RegionOperation* pOCR_Region        = NULL;
        OCR_RegionPostProcess* pOCR_PP          = NULL;
        OCR_RegionValidator*   pValidator       = NULL;

        int iTempFileNo=1;

        for (xmlpp::Node::NodeList::iterator iter = pRegions.begin(); iter!=pRegions.end();++iter) {
            pCurrentRegionNode = *iter;
            //get region name

            pCurrentRegionElement = dynamic_cast<xmlpp::Element*> (pCurrentRegionNode);
            if (pCurrentRegionElement) 
            {
                //add new region to vector

                pOCR_Region = new OCR_RegionOperation();

                // get region name
                pCurrentRegionAttribute = pCurrentRegionElement->get_attribute("name");
                pOCR_Region->setName(pCurrentRegionAttribute->get_value());

                pRegionProperties = pCurrentRegionNode->get_children();

                // iterate through region properties
                for (xmlpp::Node::NodeList::iterator reg_iter = pRegionProperties.begin(); reg_iter!=pRegionProperties.end();++reg_iter) {
                    pCurrentRegionPropNode = *reg_iter;

                    // get position
                    if (pCurrentRegionPropNode->get_name() == "position") 
                    {
                        pCurrentRegionPropElement = dynamic_cast<xmlpp::Element*> (pCurrentRegionPropNode);
                        if (pCurrentRegionPropElement) {

                           pCurrentRegionPropAttribute = pCurrentRegionPropElement->get_attribute("x1");
                           if (!pCurrentRegionPropAttribute) break;
                           pOCR_Region->setX1(atoi(pCurrentRegionPropAttribute->get_value().c_str()));

                           pCurrentRegionPropAttribute = pCurrentRegionPropElement->get_attribute("x2");
                           if (!pCurrentRegionPropAttribute) break;
                           pOCR_Region->setX2(atoi(pCurrentRegionPropAttribute->get_value().c_str()));

                           pCurrentRegionPropAttribute = pCurrentRegionPropElement->get_attribute("y1");
                           if (!pCurrentRegionPropAttribute) break;
                           pOCR_Region->setY1(atoi(pCurrentRegionPropAttribute->get_value().c_str()));

                           pCurrentRegionPropAttribute = pCurrentRegionPropElement->get_attribute("y2");
                           if (!pCurrentRegionPropAttribute) break;
                           pOCR_Region->setY2(atoi(pCurrentRegionPropAttribute->get_value().c_str()));

                        }
                    }

                    // get post process info
                    if (pCurrentRegionPropNode->get_name() == "postprocess") 
                    {
                        pCurrentRegionPropElement = dynamic_cast<xmlpp::Element*> (pCurrentRegionPropNode);
                        if (pCurrentRegionPropElement) {
                            pCurrentRegionPropAttribute = pCurrentRegionPropElement->get_attribute("mode");
                            if (!pCurrentRegionPropAttribute) break;
                            pOCR_PP = new OCR_RegionPostProcess();
                            pOCR_PP->setOperation(atoi(pCurrentRegionPropAttribute->get_value().c_str()));

                            pOCR_Region->addPostProcess(pOCR_PP);
                        }
                    }

                    // get post process info
                    if (pCurrentRegionPropNode->get_name() == "validator") 
                    {
                        pCurrentRegionPropElement = dynamic_cast<xmlpp::Element*> (pCurrentRegionPropNode);
                        if (pCurrentRegionPropElement) {
                            pCurrentRegionPropAttribute = pCurrentRegionPropElement->get_attribute("mode");
                            if (!pCurrentRegionPropAttribute) break;

                            pValidator = new OCR_RegionValidator();
                            pValidator->setMode(atoi(pCurrentRegionPropAttribute->get_value().c_str()));
                            pValidator->setOptional(false);

                            pCurrentRegionPropAttribute = pCurrentRegionPropElement->get_attribute("optional");
                            if (pCurrentRegionPropAttribute)
                                if (pCurrentRegionAttribute->get_value() == "true" || pCurrentRegionAttribute->get_value() == "TRUE") 
                                    pValidator->setOptional(true);

                            pOCR_Region->addValidator(pValidator);
                        }
                    }

                    // get other properties
                }

                if (pOCR_Region->checkRegion()==true) {

                    std::ostringstream stm ;
                    stm << iTempFileNo++;

                    pOCR_Region->setTempFileName(szPath+"/"+szFileName+stm.str());

                    regions.push_back(pOCR_Region);
                    pOCR_Region = NULL;
                } else {
                    delete pOCR_Region;
                    pOCR_Region = NULL;
                }

            }
        }
    } catch (std::exception &e) {
        // log exception and throw error code
        throw LOAD_TEMPLATE_EXCEPTION;
    }
}

void OCR_Parser::process_ocr() throw(int)
{
    try {
        for (int i = 0;i<regions.size();i++) {
            regions[i]->setBaseImage(pImage);
            regions[i]->processImage();

            std::cout << regions[i]->getOCRText() << "\n";
        }
    } catch (std::exception &e) {
        // log exception and throw error code
        throw PROCESS_OCR_EXCEPTION;
    }
}

void OCR_Parser::loadImage(std::string image_file) throw(int)
{
    try {
        pImage.read(image_file);
        szImageFileName = image_file;
    } catch (std::exception &e) {
        // log exception and throw error code
        throw LOAD_IMAGE_EXCEPTION;
    }
}