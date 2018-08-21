#pragma once
#include <string>
#include <unordered_map>
#include "Animation.h"

namespace di
{
    class Animation_manager
    {
    public:
        Animation_manager(const Animation_manager&) = delete;
        Animation_manager& operator=(const Animation_manager&) = delete;

        std::shared_ptr<Animation> get(const std::string);
        static Animation_manager* instance();
    private:
        std::unordered_map<std::string, std::shared_ptr<Animation>> resources;
        Animation_manager();
    };
}
