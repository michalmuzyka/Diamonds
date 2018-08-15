#pragma once
#include "Animated_sprite.h"
#include <string>
#include <SFML/Window/Mouse.hpp>

namespace di
{

    class Tile :public sf::Drawable
    {
    public:
        Tile();
        explicit Tile(const unsigned &type);
        void update(const unsigned long long&delta_time, const sf::Vector2i& mouse_pos);
        void set_position(float x, float y);
        bool hover(const sf::Vector2i& mouse_pos);
        Animated_sprite sprite;
    private:
        sf::Sprite border;
        unsigned type;
        bool hovered;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
