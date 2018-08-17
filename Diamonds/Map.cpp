#include "stdafx.h"
#include "Map.h"
#include "Settings.h"
#include "Random_int.h"

namespace di
{

    Map::Map(const unsigned x, const unsigned y)
    :x(x), y(y), time_offset(0){
      
    }

    void Map::init() {
        for (int i = 0; i != y; ++i) {
            map.emplace_back();
            for (int z = 0; z != x; ++z) {
                
                map[i].emplace_back(z,i);
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

            map[f_y][f_x].unclick();
            map[s_y][s_x].unclick();

            map[f_y][f_x].change_type(&map[s_y][s_x]);

            map[f_y][f_x].set_sprite_position(s_x * 100, s_y * 100);
            map[s_y][s_x].set_sprite_position(f_x * 100, f_y * 100);

            Settings::instance()->set("in_swap_animation", "1");
            Settings::instance()->set("block_input", "1");
        }

        if(Settings::instance()->get_int("in_swap_animation")){
            const unsigned long long swap_animation_offset = Settings::instance()->get_ull("swap_animation_offset");
            const int f_x = Settings::instance()->get_int("first_x");
            const int f_y = Settings::instance()->get_int("first_y");
            const int s_x = Settings::instance()->get_int("second_x");
            const int s_y = Settings::instance()->get_int("second_y");
            
            if(map[f_y][f_x].get_sprite_position() == sf::Vector2f(f_x*100,f_y*100)){
                Settings::instance()->set("in_swap_animation", "0");
                Settings::instance()->set("block_input", "0");
                time_offset = 0;
            }else{
                if (time_offset > swap_animation_offset) {
                    map[f_y][f_x].sprite.move((f_x - s_x) * 10, (f_y - s_y) * 10);
                    map[s_y][s_x].sprite.move((s_x - f_x) * 10, (s_y - f_y) * 10);
                    time_offset %= swap_animation_offset;
                }
                time_offset += delta_time;
            }
        }
    }

}
