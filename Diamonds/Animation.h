#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>

namespace di
{

    class Animation
    {
    public:
        Animation();
        void add_frame(const sf::IntRect&);
        void generate_frames_from_line(const sf::Vector2u&);
        void set_sheet(std::shared_ptr<sf::Texture>);
        std::size_t get_animation_length() const;
        sf::IntRect get_frame(const std::size_t &n) const;
        std::shared_ptr<sf::Texture> get_sheet() const;

    private:
        std::vector<sf::IntRect> frames;
        std::shared_ptr<sf::Texture> sheet;
    };

}