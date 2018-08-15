#include "stdafx.h"
#include "Animation.h"

namespace di
{

    Animation::Animation()
    {
    }

    void Animation::add_frame(const sf::IntRect&frame){
        frames.push_back(frame);
    }

    void Animation::generate_frames_from_line(const sf::Vector2u& size) {
        unsigned count_of_frames = 0;
        const auto max_size = sheet->getSize();
        for(unsigned i=0; i!=max_size.x/size.x; ++i){
            add_frame(sf::IntRect(i*size.x, 0, size.x, size.y));
        }
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