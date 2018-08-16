#pragma once
#include "Animated_sprite.h"
#include <string>
#include <SFML/Window/Mouse.hpp>

namespace di
{

    class Tile :public sf::Drawable
    {
    public:
        Tile(const int &x, const int &y);
        explicit Tile(const unsigned &type, const int &x, const int &y);
        void update(const unsigned long long&delta_time, const sf::Vector2i& mouse_pos);
        void set_position(float x, float y);
        void hover(const sf::Vector2i& mouse_pos);
        void click();
        void unclick();
        bool isClicked() const;
        void changeType(Tile*tile);
        Animated_sprite sprite;
    private:
        sf::Sprite hover_border, border;
        unsigned type;
        bool hovered;
        bool clicked;
        unsigned long long time_offset;
        int x, y;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
