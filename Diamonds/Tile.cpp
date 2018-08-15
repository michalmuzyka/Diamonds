#include "stdafx.h"
#include "Tile.h"
#include "Random_int.h"
#include <iostream>
#include "Animation_manager.h"

namespace di
{

    Tile::Tile()
    :type(di::Random_int::get(1,6)){
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type)+"_s.png"));
    }

    Tile::Tile(const unsigned& type)
    :type(type){
        sprite.set_animation(Animation_manager::instance()->get(std::to_string(type) + "_s.png"));
    }

    void Tile::update(const unsigned long long& delta_time) {
        sprite.update(delta_time);
    }

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    }

}
