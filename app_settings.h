/* 
 * File:   app_settings.h
 * Author: dan
 *
 * Created on May 27, 2015, 9:43 AM
 */

#ifndef APP_SETTINGS_H
#define	APP_SETTINGS_H

#include <unordered_map>
#include <string>

class app_settings {
    
public:
    
    app_settings();
    virtual ~app_settings();
    
    std::string getSetting(std::string key);
    void loadSettings();
    
private:
    
    std::unordered_map<std::string,std::string> mapSettings;

    app_settings(app_settings const&);
    void operator=(app_settings const &);
    
};

#endif	/* APP_SETTINGS_H */

