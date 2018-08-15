#pragma once
#include <unordered_map>

namespace di
{
    class Settings
    {
    public:        
        Settings(const Settings&) = delete;
        Settings& operator=(const Settings&) = delete;

        void set(const std::string &, const std::string &);
        std::string get_string(const std::string &);
        int get_int(const std::string &);
        float get_float(const std::string &);
        static Settings* instance();
    private:
        std::unordered_map<std::string, std::string> settings;
        Settings();
    };

}