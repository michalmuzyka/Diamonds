#pragma once
#include <string>
#include <SFML/Window/Mouse.hpp>
#include "Animated_sprite.h"

namespace di
{

    class Tile :public sf::Drawable
    {
    public:
        Tile(const int &x, const int &y);
        void update(const unsigned long long&delta_time, const sf::Vector2i& mouse_pos);
        void set_position(float x, float y);
        sf::Vector2f get_sprite_position() const;
        void hover(const sf::Vector2i& mouse_pos);
        void click();
        void unclick();
        bool is_clicked() const;
        void change_type(Tile*tile);
        unsigned get_type() const;
        void set_random_type();
        void set_type(const unsigned&);
        sf::FloatRect get_sprite_bounds() const;
        void move_sprite(const float &x,const float &y);
    private:
        Animated_sprite sprite;
        sf::Sprite hover_sprite, border;
        unsigned type;
        bool hovered;
        bool clicked;
        unsigned long long swap_time_offset;
        int number_of_tiles_x, number_of_tiles_y;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
