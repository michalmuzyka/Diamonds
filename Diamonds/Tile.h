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
        void set_sprite_position(float x, float y);
        sf::Vector2f get_sprite_position() const;
        void hover(const sf::Vector2i& mouse_pos);
        void click();
        void unclick();
        bool is_clicked() const;
        void change_type(Tile*tile);
        unsigned get_type() const;
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
