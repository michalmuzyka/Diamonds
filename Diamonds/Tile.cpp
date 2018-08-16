#include "stdafx.h"
#include "Tile.h"
#include "Random_int.h"
#include "Animation_manager.h"
#include "Texture_manager.h"
#include "Settings.h"
#include <iostream>

namespace di
{

    Tile::Tile()
    :type(di::Random_int::get(1,6)), hovered(false), clicked(false), time_offset(0){
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type)+"_s.png"));
        border.setTexture(*Texture_manager::instance()->get("border.png"));
    }

    Tile::Tile(const unsigned& type)
    :type(type), hovered(false), clicked(false){
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type) + "_s.png"));
        border.setTexture(*Texture_manager::instance()->get("border.png"));
    }

    void Tile::update(const unsigned long long& delta_time, const sf::Vector2i& mouse_pos) {
        sprite.update(delta_time);
        time_offset += delta_time;
       
        hover(mouse_pos);
        click();

    }

    void Tile::hover(const sf::Vector2i& mouse_pos) {
        if (sprite.getBounds().contains(sf::Vector2f(mouse_pos.x, mouse_pos.y))){
            hovered = true;
        } else{
            hovered = false;
        }
    }

    void Tile::click() {
        const unsigned long long settings_update_time = Settings::instance()->get_ull("update_time");

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (hovered) {
                if (settings_update_time < time_offset) {
                    time_offset %= settings_update_time;
                    clicked = !clicked;
                    std::cout << clicked << '\n';
                }
            }
        }
    }

    void Tile::unclick() {
        clicked = false;
    }

    bool Tile::isClicked() const {
        return clicked;
    }

    void Tile::set_position(float x, float y) {
        sprite.setPosition(x, y);
        border.setPosition(x, y);
    }

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
        if (hovered || clicked)
            target.draw(border);
    }

}
