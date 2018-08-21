#include <string>
#include <iostream>
#include "Settings.h"

namespace di
{

    Settings::Settings()
    {

    }

    void Settings::set(const std::string key, const std::string value){
        settings[key] = value;
    }
    void Settings::set(const std::string key, const int value){
        settings[key] = std::to_string(value);
    }
    void Settings::set(const std::string key, const double value){
        settings[key] = std::to_string(value);
    }
    void Settings::set(const std::string key, const float value){
        settings[key] = std::to_string(value);
    }
    void Settings::set(const std::string key, const unsigned value){
        settings[key] = std::to_string(value);
    }
    void Settings::set(const std::string key, const long long value){
        settings[key] = std::to_string(value);
    }
    void Settings::set(const std::string key, const unsigned long long value){
        settings[key] = std::to_string(value);
    }
    void Settings::add(const std::string key, const int value) {
        settings[key] = std::to_string(std::stoi(settings[key]) + value);
    }

    std::string Settings::get_string(const std::string key) {
        if(settings.find(key)==settings.end()){
            return "";
        }
        
        return settings[key];
    }

    int Settings::get_int(const std::string key) {
        if (settings.find(key) == settings.end()) {
            return 0;
        }

        return std::stoi(settings[key]);
    }

    float Settings::get_float(const std::string key)
    {
        if (settings.find(key) == settings.end()) {
            return 0;
        }

        return std::stof(settings[key]);
    }

    double Settings::get_double(const std::string key) {
        if (settings.find(key) == settings.end()) {
            return 0;
        }

        return std::stod(settings[key]);
    }

    long long Settings::get_ll(const std::string key) {
        if (settings.find(key) == settings.end()) {
            return 0;
        }

        return std::stoll(settings[key]);
    }

    unsigned long long Settings::get_ull(const std::string key) {
        if (settings.find(key) == settings.end()) {
            return 0;
        }

        return std::stoull(settings[key]);
    }

    Settings* Settings::instance() {
        static Settings settings;
        return &settings;
    }


}
