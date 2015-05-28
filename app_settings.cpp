/* 
 * File:   app_settings.cpp
 * Author: dan
 * 
 * Created on May 27, 2015, 9:43 AM
 */

#include "app_settings.h"
#include <libxml++/libxml++.h>
#include <glibmm-2.4/glibmm/ustring.h>

app_settings* app_settings::instance = NULL;

const std::string app_settings::SERVER_PORT             = "listenPort";
const std::string app_settings::MAX_SERVER_CONNECTIONS  = "maxConnections";
const std::string app_settings::MAX_OCR_THREADS         = "maxOCRThreads";

app_settings* app_settings::Instance() {
    
    if (!instance) {
        instance = new app_settings();
        instance->loadSettings();
    }
    
    return instance;
}

app_settings::app_settings() {
}

std::string app_settings::getSetting(std::string key)
{
    return mapSettings[key];
}

void app_settings::loadSettings()
{
    xmlpp::DomParser parser;
    
    parser.parse_file("settings.xml");
    
    if (!parser) return;
    
    xmlpp::Node* pMainNode = parser.get_document()->get_root_node();
    
    xmlpp::Node::NodeList pSettingsList = pMainNode->get_children();
    
    xmlpp::Element*     pCurrentElement = NULL;
    xmlpp::Node*        pCurrentNode = NULL;
    xmlpp::Attribute*   pCurrentAttribute = NULL;
    
    for (xmlpp::Node::NodeList::iterator iter = pSettingsList.begin(); iter!=pSettingsList.end();++iter) {
        
        pCurrentNode = *iter;
        pCurrentElement = dynamic_cast<xmlpp::Element*>(pCurrentNode);
        
        if (pCurrentElement) 
        {
            if (pCurrentElement->get_name() == "listen")
            {
                // daemon listen port
                pCurrentAttribute = pCurrentElement->get_attribute("port");
                if (pCurrentAttribute)
                    mapSettings[SERVER_PORT] = pCurrentAttribute->get_value();
                else
                    mapSettings[SERVER_PORT] = "46466";
                
                pCurrentAttribute = pCurrentElement->get_attribute("maxconnections");
                if (pCurrentAttribute)
                    mapSettings[MAX_SERVER_CONNECTIONS] = pCurrentAttribute->get_value();
                else
                    mapSettings[MAX_SERVER_CONNECTIONS] = "10";
            }
            
            if (pCurrentElement->get_name() == "ocr") {
                // daemon listen port
                pCurrentAttribute = pCurrentElement->get_attribute("maxregionthreads");
                if (pCurrentAttribute)
                    mapSettings[MAX_OCR_THREADS] = pCurrentAttribute->get_value();
                else
                    mapSettings[MAX_OCR_THREADS] = "4";
            }
        }
    }
}

