#include "stdafx.h"
#include "Animation.h"

namespace di
{

    Animation::Animation()
    {
    }


    Animation::~Animation()
    {
    }

    void Animation::add_frame(const sf::IntRect&frame){
        frames.push_back(frame);
    }

    std::size_t Animation::get_animation_length() const {
        return frames.size();
    }

    sf::IntRect Animation::get_frame(const std::size_t& n) const {
        return frames[n];
    }

    std::shared_ptr<sf::Texture> Animation::get_sheet() const {
        return sheet;
    }

    void Animation::set_sheet(std::shared_ptr<sf::Texture> sprite_sheet) {
        sheet = sprite_sheet;
    }

}