#include "stdafx.h"
#include "Tile.h"
#include "Random_int.h"
#include "Animation_manager.h"
#include "Texture_manager.h"

namespace di
{

    Tile::Tile()
    :type(di::Random_int::get(1,6)), hovered(false){
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type)+"_s.png"));
        border.setTexture(*Texture_manager::instance()->get("border.png"));
    }

    Tile::Tile(const unsigned& type)
    :type(type), hovered(false){
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type) + "_s.png"));
        border.setTexture(*Texture_manager::instance()->get("border.png"));
    }

    void Tile::update(const unsigned long long& delta_time, const sf::Vector2i& mouse_pos) {
        sprite.update(delta_time);
        hover(mouse_pos);
    }

    bool Tile::hover(const sf::Vector2i& mouse_pos) {
        if (sprite.getBounds().contains(sf::Vector2f(mouse_pos.x, mouse_pos.y))){
            hovered = true;
        } else{
            hovered = false;
        }

        return hovered;
    }

    void Tile::set_position(float x, float y) {
        sprite.setPosition(x, y);
        border.setPosition(x, y);
    }

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
        if (hovered)
            target.draw(border);
    }

}
