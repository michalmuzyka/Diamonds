#include "stdafx.h"
#include "Animation_manager.h"

namespace di
{
    Animation_manager::Animation_manager() {
        
    }

    std::shared_ptr<Animation> Animation_manager::get(const std::string&s) {
        if(resources.find(s)==resources.end()){
            resources[s] = std::make_shared<Animation>();
        }
        return resources[s];
    }

    Animation_manager* Animation_manager::instance() {
        static Animation_manager manager;
        return &manager;
    }
}