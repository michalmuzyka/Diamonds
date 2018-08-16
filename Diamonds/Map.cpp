#include "stdafx.h"
#include "Map.h"
#include "Settings.h"

namespace di
{

    Map::Map(const unsigned x, const unsigned y)
    :x(x), y(y){
      
    }

    void Map::init() {
        for (int i = 0; i != x; ++i) {
            map.emplace_back();
            for (int z = 0; z != y; ++z) {
                map[i].emplace_back(i,z);
                map[i][z].set_position(z * 100, i * 100);
            }
        }

        const auto bounds = map[0][0].sprite.getBounds();
        tile_size = sf::Vector2f(bounds.width, bounds.height);
    }


    void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto &m : map)
            for (auto &s : m)
                target.draw(s);
    }

    void Map::update(const unsigned long long& delta_time, const sf::Vector2i& mouse_pos) {
        for (auto &m : map)
            for (auto &s : m) {
                s.update(delta_time, mouse_pos);
            }

        if(Settings::instance()->get_int("first_clicked")&& Settings::instance()->get_int("second_clicked")){
            const int f_x = Settings::instance()->get_int("first_x");
            const int f_y = Settings::instance()->get_int("first_y");
            const int s_x = Settings::instance()->get_int("second_x");
            const int s_y = Settings::instance()->get_int("second_y");
            Settings::instance()->set("first_clicked", "0");
            Settings::instance()->set("second_clicked", "0");

            map[f_x][f_y].unclick();
            map[s_x][s_y].unclick();

            map[f_x][f_y].changeType(&map[s_x][s_y]);
 
        }
    }

}
