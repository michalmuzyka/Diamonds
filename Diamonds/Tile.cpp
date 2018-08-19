#include "stdafx.h"
#include "Tile.h"
#include "Random_int.h"
#include "Animation_manager.h"
#include "Texture_manager.h"
#include "Settings.h"
#include <iostream>

namespace di
{

    Tile::Tile(const int &x, const int &y)
    :type(di::Random_int::get(1,6)), hovered(false), clicked(false), swap_time_offset(0), number_of_tiles_x(x), number_of_tiles_y(y){
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type)+"_s.png"));
        border.setTexture(*Texture_manager::instance()->get("border.png"));
        hover_sprite.setTexture(*Texture_manager::instance()->get("border-hover.png"));
    }

    Tile::Tile(const unsigned& type, const int &x, const int &y)
    :type(type), hovered(false), clicked(false),number_of_tiles_x(x), number_of_tiles_y(y){
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type) + "_s.png"));
        border.setTexture(*Texture_manager::instance()->get("border.png"));
        hover_sprite.setTexture(*Texture_manager::instance()->get("border-hover.png"));
    }

    void Tile::update(const unsigned long long& delta_time, const sf::Vector2i& mouse_pos) {
        sprite.update(delta_time);
        swap_time_offset += delta_time;
       
        hover(mouse_pos);
        click();

    }

    void Tile::change_type(Tile* tile) {
        std::swap(tile->type, type);
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type) + "_s.png"));
        tile->sprite.set_animation(Animation_manager::instance()->get(std::to_string(tile->type) + "_s.png"));
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
        if (!Settings::instance()->get_int("block_input")) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if (hovered) {
                    if (settings_update_time < swap_time_offset) {
                        swap_time_offset %= settings_update_time;
                        if (clicked) {
                            if (Settings::instance()->get_int("first_clicked")) {
                                if (Settings::instance()->get_int("first_x") == number_of_tiles_x && Settings::instance()->get_int("first_y") == number_of_tiles_y) {
                                    Settings::instance()->set("first_clicked", 0);
                                    clicked = false;
                                }
                            }
                        }
                        else {
                            if (Settings::instance()->get_int("first_clicked")) {
                                int f_x = Settings::instance()->get_int("first_x");
                                int f_y = Settings::instance()->get_int("first_y");

                                if ((abs(f_x - number_of_tiles_x) == 1 && abs(f_y - number_of_tiles_y) == 0) || (abs(f_x - number_of_tiles_x) == 0 && abs(f_y - number_of_tiles_y) == 1)) {
                                    Settings::instance()->set("second_clicked", 1);
                                    Settings::instance()->set("second_x", number_of_tiles_x);
                                    Settings::instance()->set("second_y", number_of_tiles_y);
                                    clicked = true;
                                }else{
                                    clicked = true;
                                    Settings::instance()->set("first_x", number_of_tiles_x);
                                    Settings::instance()->set("first_y", number_of_tiles_y);
                                    Settings::instance()->set("unclick", 1);
                                    Settings::instance()->set("unclick_x", f_x);
                                    Settings::instance()->set("unclick_y", f_y);
                                }
                            }
                            else {
                                Settings::instance()->set("first_clicked", 1);
                                Settings::instance()->set("first_x", number_of_tiles_x);
                                Settings::instance()->set("first_y", number_of_tiles_y);
                                clicked = true;
                            }
                        }
                    }
                }
            }
        }
    }

    unsigned Tile::get_type() const {
        return type;
    }

    void Tile::set_random_type() {
        type = di::Random_int::get(1, 6);
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type) + "_s.png"));
    }

    void Tile::set_type(const unsigned &type){
        this->type = type;
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type) + "_s.png"));
    }

    sf::FloatRect Tile::get_sprite_bounds() const {
        return sprite.getBounds();
    }

    void Tile::move_sprite(const float& x, const float& y) {
        sprite.move(x, y);
    }

    void Tile::unclick() {
        clicked = false;
    }

    bool Tile::is_clicked() const {
        return clicked;
    }

    void Tile::set_position(float x, float y) {
        sprite.setPosition(x, y);
        border.setPosition(x, y);
        hover_sprite.setPosition(x, y);
    }

    void Tile::set_sprite_position(float x, float y) {
        sprite.setPosition(x, y);
    }

    sf::Vector2f Tile::get_sprite_position() const {
        return sprite.getPosition();
    }

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
        if (clicked)
            target.draw(border);
        if (hovered && !Settings::instance()->get_int("block_input"))
            target.draw(hover_sprite);
    }

}
