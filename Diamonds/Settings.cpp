#include "stdafx.h"
#include "Settings.h"
#include <string>

namespace di
{

    Settings::Settings(){

    }

    void Settings::set(const std::string &key, const std::string &value) {
        settings[key] = value;
    }

    std::string Settings::get_string(const std::string &key) {
        if(settings.find(key)==settings.end()){
            return "";
        }
        
        return settings[key];
    }

    int Settings::get_int(const std::string& key) {
        if (settings.find(key) == settings.end()) {
            return 0;
        }

        return std::stoi(settings[key]);
    }

    float Settings::get_float(const std::string& key)
    {
        if (settings.find(key) == settings.end()) {
            return 0;
        }

        return std::stof(settings[key]);
    }

    Settings* Settings::instance() {
        static Settings settings;
        return &settings;
    }


}
