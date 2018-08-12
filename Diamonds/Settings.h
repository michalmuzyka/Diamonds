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
        std::string get(const std::string &);
        static Settings* instance();
    private:
        std::unordered_map<std::string, std::string> settings;
        Settings();
    };

}