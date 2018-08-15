#include "stdafx.h"
#include "Map.h"

namespace di
{

    Map::Map(const unsigned x, const unsigned y)
    :x(x), y(y){
      
    }

    void Map::init() {
        for (int i = 0; i != x; ++i) {
            map.emplace_back();
            for (int z = 0; z != y; ++z) {
                map[i].emplace_back();
                map[i][z].sprite.setPosition(z * 100, i * 100);
            }
        }

        const auto bounds = map[0][0].sprite.getBounds();
        tile_size = sf::Vector2f(bounds.width, bounds.height);
    }

    void Map::scale(const float x, const float y) {
        for (auto &m : map)
            for (auto &s : m)
                s.sprite.scale(x,y);

        const auto bounds = map[0][0].sprite.getBounds();
        tile_size = sf::Vector2f(bounds.width, bounds.height);
    }


    void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto &m : map)
            for (auto &s : m)
                target.draw(s);
    }

    void Map::update(const unsigned long long& delta_time) {
        for (auto &m : map)
            for (auto &s : m)
                s.update(delta_time);
    }

}