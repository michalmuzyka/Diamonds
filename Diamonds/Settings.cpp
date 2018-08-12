#include "stdafx.h"
#include "Settings.h"

namespace di
{

    Settings::Settings(){

    }

    void Settings::set(const std::string &key, const std::string &value) {
        settings[key] = value;
    }

    std::string Settings::get(const std::string &key) {
        if(settings.find(key)==settings.end()){
            return "";
        }
        
        return settings[key];
    }

    Settings* Settings::instance() {
        static Settings settings;
        return &settings;
    }


}