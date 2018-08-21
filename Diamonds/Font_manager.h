#pragma once
#include <unordered_map>
#include <memory>

namespace sf {
    class Font;
}

namespace di
{
    class Font_manager
    {
    public:
        Font_manager(const Font_manager&) = delete;
        Font_manager& operator=(const Font_manager&) = delete;

        void set_folder_path(const std::string);
        std::shared_ptr<sf::Font> get(const std::string);
        std::shared_ptr<sf::Font> get_default();
        static Font_manager* instance();
    private:
        std::unordered_map<std::string, std::shared_ptr<sf::Font>> resources;
        std::string folder_path;
        Font_manager();
    };

}

