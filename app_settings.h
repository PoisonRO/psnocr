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
    
    const static std::string    SERVER_PORT;
    const static std::string    MAX_SERVER_CONNECTIONS;
    const static std::string    MAX_OCR_THREADS;
    
    static app_settings* Instance();
    
    std::string getSetting(std::string key);
    
private:
    
    app_settings();
    
    std::unordered_map<std::string,std::string> mapSettings;

    void loadSettings();
    
    app_settings(app_settings const&);
    void operator=(app_settings const &);
    
    static app_settings    *instance;
};

#endif	/* APP_SETTINGS_H */

