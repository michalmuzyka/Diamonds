#pragma once
#include <unordered_map>

namespace di
{
    class Settings
    {
    public:        
        Settings(const Settings&) = delete;
        Settings& operator=(const Settings&) = delete;

        void set(const std::string &, const int&);
        void set(const std::string& key, const double& value);
        void set(const std::string& key, const float& value);
        void set(const std::string& key, const unsigned& value);
        void set(const std::string& key, const long long& value);
        void set(const std::string& key, const unsigned long long& value);
        void add(const std::string& key, const int& value);
        void set(const std::string &, const std::string &);
        std::string get_string(const std::string &);
        int get_int(const std::string &);
        float get_float(const std::string &);
        double get_double(const std::string &);
        unsigned long long get_ull(const std::string &);
        long long get_ll(const std::string &);
        static Settings* instance();
    private:
        std::unordered_map<std::string, std::string> settings;
        Settings();
    };

}