#pragma once
#include <unordered_map>
#include <memory>

namespace di
{
    class Texture_manager
    {
    public:
        Texture_manager(const Texture_manager&) = delete;
        Texture_manager& operator=(const Texture_manager&) = delete;

        void set_folder_path(const std::string&);
        std::shared_ptr<sf::Texture> get(const std::string&);
        static Texture_manager* instance();
    private: 
        std::unordered_map<std::string, std::shared_ptr<sf::Texture>> resources;
        std::string folder_path;
        Texture_manager();
    };

}
