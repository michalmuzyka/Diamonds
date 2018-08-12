#include "stdafx.h"
#include "Font_manager.h"


namespace di
{
    Font_manager::Font_manager()
    {
        set_folder_path("data/font/");
        resources["default"] = std::make_shared<sf::Font>(sf::Font());
        resources["default"]->loadFromFile(folder_path+"default.ttf");
    }

    void Font_manager::set_folder_path(const std::string& folder_path)
    {
        this->folder_path = folder_path;

        if (folder_path[folder_path.length() - 1] != '/')
            this->folder_path += '/';
    }

    Font_manager* Font_manager::instance()
    {
        static Font_manager manager;
        return &manager;
    }

    std::shared_ptr<sf::Font> Font_manager::get(const std::string &name)
    {
        if (resources.find(folder_path + name) == resources.end()) {
            resources[folder_path + name] = std::make_shared<sf::Font>(sf::Font());
            resources[folder_path + name]->loadFromFile(folder_path + name);
        }

        return resources[folder_path + name];
    }
    
    std::shared_ptr<sf::Font> Font_manager::get_default() {
        return resources["default"];
    }

}
