#include "stdafx.h"
#include "Texture_manager.h"

namespace di
{
    Texture_manager::Texture_manager()
    {
       set_folder_path("data/textures/");
    }

    void Texture_manager::set_folder_path(const std::string& folder_path)
    {
        this->folder_path = folder_path;

        if (folder_path[folder_path.length() - 1] != '/')
            this->folder_path += '/';
    }

    Texture_manager* Texture_manager::instance() {
        static Texture_manager manager;
        return &manager;
    }

    std::shared_ptr<sf::Texture> Texture_manager::get(const std::string &name)
    {
        if (resources.find(name) == resources.end()) {
            resources[name] = std::make_shared<sf::Texture>(sf::Texture());
            resources[name]->loadFromFile(folder_path+name);
        }

        return resources[name];
    }

}