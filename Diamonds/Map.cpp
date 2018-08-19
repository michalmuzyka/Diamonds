#include "stdafx.h"
#include "Map.h"
#include "Settings.h"
#include "Random_int.h"
#include <iostream>

namespace di
{

    Map::Map()
    :x(0), y(0), swap_time_offset(0), solve_time_offset(0), x_offset(0), y_offset(0){
      
    }

    void Map::init(const unsigned x, const unsigned y){
        this->x = x;
        this->y = y;

        x_offset = (Settings::instance()->get_int("screen_width")-x*100)/2;
        y_offset = (Settings::instance()->get_int("screen_height")-y*100)/2;
        Settings::instance()->set("x_offset", x_offset);
        Settings::instance()->set("y_offset", y_offset);
        Settings::instance()->set("points", 0);

        for (int i = 0; i != y; ++i) {
            map.emplace_back();
            for (int z = 0; z != x; ++z) {
                
                map[i].emplace_back(z,i);
                map[i][z].set_position(x_offset+z * 100, y_offset+ i * 100);
            }
        }

        make_map_without_completed_puzzle();

        const auto bounds = map[0][0].sprite.getBounds();
        tile_size = sf::Vector2f(bounds.width, bounds.height);
    }

    void Map::make_map_without_completed_puzzle()
    {
        for (int i = 0; i != y; ++i) {
            for (int z = 0; z != x; ++z) {
                //map without border
                if (z != 0 && z != x - 1 && i != 0 && i != y - 1) {
                    bool found_completed_puzzle = false;
                    char vertical_type = -1, horizontal_type=-1;
                    if (map[i][z].get_type() == map[i - 1][z].get_type() && map[i][z].get_type() == map[i + 1][z].get_type()) {
                        found_completed_puzzle = true;
                        vertical_type = map[i][z].get_type();
                    }
                    if (map[i][z].get_type() == map[i][z-1].get_type() && map[i][z].get_type() == map[i][z+1].get_type()) {
                        found_completed_puzzle = true;
                        horizontal_type = map[i][z].get_type();
                    }
                    if (found_completed_puzzle) {
                        int new_type = Random_int::get(1, 6);
                        while (new_type == vertical_type||new_type==horizontal_type)
                            new_type = Random_int::get(1, 6);
                        map[i][z].set_type(new_type);
                    }
                }

                //left and right border
                if (z == 0 || z == x - 1){
                    if (i != 0 && i != y - 1) {
                        bool found_completed_puzzle = false;
                        char completed_type = -1;
                        if (map[i][z].get_type() == map[i - 1][z].get_type() && map[i][z].get_type() == map[i + 1][z].get_type()) {
                            found_completed_puzzle = true;
                            completed_type = map[i][z].get_type();
                        }
                        if (found_completed_puzzle) {
                            int new_type = Random_int::get(1, 6);
                            while (new_type == completed_type)
                                new_type = Random_int::get(1, 6);
                            map[i][z].set_type(new_type);
                        }
                    }
                }

                //top and bottom border
                if (i == 0 || i == y - 1) {
                    if (z != 0 && z != x - 1) {
                        bool found_completed_puzzle = false;
                        char completed_type = -1;
                        if (map[i][z].get_type() == map[i][z-1].get_type() && map[i][z].get_type() == map[i][z+1].get_type()) {
                            found_completed_puzzle = true;
                            completed_type = map[i][z].get_type();
                        }
                        if (found_completed_puzzle) {
                            int new_type = Random_int::get(1, 6);
                            while (new_type == completed_type)
                                new_type = Random_int::get(1, 6);
                            map[i][z].set_type(new_type);
                        }
                    }
                }
            }
        }
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

        if(Settings::instance()->get_int("unclick")){
            const int x = Settings::instance()->get_int("unclick_x");
            const int y = Settings::instance()->get_int("unclick_y");
            map[y][x].unclick();
            Settings::instance()->set("unclick", 0);
        }

        if(Settings::instance()->get_int("first_clicked")&& Settings::instance()->get_int("second_clicked")){
            prepare_swap_animation();
        }

        if(Settings::instance()->get_int("in_swap_animation")){
            update_swap_animation(delta_time);
        }
        
        if (!Settings::instance()->get_int("block_input")) {
            if (check_map()) {
                prepare_solve_animation();
            }
        }
        
        if(Settings::instance()->get_int("in_solve_animation")){
            update_solve_animation(delta_time);
        }

    }

    bool Map::check_map() {
        
        //horizontal check
        if (!Settings::instance()->get_int("horizontal_check") && !Settings::instance()->get_int("vertical_check")) {
            for (int i = 0; i != y; ++i) {
                unsigned last = map[i][0].get_type();
                unsigned counter = 0;
                for (int s = 1; s != x; ++s) {
                    if (map[i][s].get_type() == last && s != x - 1) ++counter;
                    else {
                        int offset = 0;
                        if (map[i][s].get_type() == last) {
                            ++counter;
                            offset = 1;
                        }

                        if (counter >= 2) {
                            Settings::instance()->set("horizontal_check", 1);
                            Settings::instance()->set("horizontal_x", s+offset-1);
                            Settings::instance()->set("horizontal_y", i);
                            Settings::instance()->set("horizontal_count", counter);
                            return true;
                        }
                        else {
                            counter = 0;
                        }
                        last = map[i][s].get_type();
                    }
                }
            }
            
            //vertical check
            for (int i = 0; i != x; ++i) {
                unsigned last = map[0][i].get_type();
                unsigned counter = 0;
                for (int s = 1; s != y; ++s) {
                    if (map[s][i].get_type() == last && s != y - 1) ++counter;
                    else {
                        int offset = 0;
                        if (map[s][i].get_type() == last) {
                            ++counter;
                            offset = 1;
                        }

                        if (counter >= 2) {
                            Settings::instance()->set("vertical_check", 1);
                            Settings::instance()->set("vertical_x", i);
                            Settings::instance()->set("vertical_y", s+offset-1);
                            Settings::instance()->set("vertical_count", counter);
                            return true;
                        }
                        else {
                            counter = 0;
                        }
                        last = map[s][i].get_type();
                    }
                }
            }
            
        }

        return false;
    }

    void Map::prepare_swap_animation() {
        const int f_x = Settings::instance()->get_int("first_x");
        const int f_y = Settings::instance()->get_int("first_y");
        const int s_x = Settings::instance()->get_int("second_x");
        const int s_y = Settings::instance()->get_int("second_y");
        Settings::instance()->set("first_clicked", 0);
        Settings::instance()->set("second_clicked", 0);

        map[f_y][f_x].unclick();
        map[s_y][s_x].unclick();

        map[f_y][f_x].change_type(&map[s_y][s_x]);

        map[f_y][f_x].set_sprite_position(x_offset + s_x * 100, y_offset + s_y * 100);
        map[s_y][s_x].set_sprite_position(x_offset + f_x * 100, y_offset + f_y * 100);

        Settings::instance()->set("in_swap_animation", 1);
        Settings::instance()->set("block_input", 1);
    }

    void Map::update_swap_animation(const unsigned long long& delta_time) {
        const unsigned long long swap_animation_offset = Settings::instance()->get_ull("swap_animation_offset");
        const int f_x = Settings::instance()->get_int("first_x");
        const int f_y = Settings::instance()->get_int("first_y");
        const int s_x = Settings::instance()->get_int("second_x");
        const int s_y = Settings::instance()->get_int("second_y");

        if (map[f_y][f_x].get_sprite_position() == sf::Vector2f(x_offset + f_x * 100, y_offset + f_y * 100)) {
            Settings::instance()->set("in_swap_animation", 0);
            Settings::instance()->set("block_input", 0);
            swap_time_offset = 0;
        }
        else {
            if (swap_time_offset > swap_animation_offset) {
                map[f_y][f_x].sprite.move((f_x - s_x) * 10, (f_y - s_y) * 10);
                map[s_y][s_x].sprite.move((s_x - f_x) * 10, (s_y - f_y) * 10);
                swap_time_offset %= swap_animation_offset;
            }
            swap_time_offset += delta_time;
        }
    }

    void Map::prepare_solve_animation() {
        if (Settings::instance()->get_int("horizontal_check")) {
            const int x = Settings::instance()->get_int("horizontal_x");
            const int y = Settings::instance()->get_int("horizontal_y");
            const unsigned count = Settings::instance()->get_int("horizontal_count");
            Settings::instance()->set("update_points", 1);
            Settings::instance()->add("points", (count+1 + (count -2)*(count - 2)) * 10);
            for (int i = y; i != -1; --i) {
                for (int s = 0; s <= count; ++s) {
                    if (i != 0) {
                        map[i][x - s].set_type(map[i - 1][x - s].get_type());
                    }
                    else {
                        map[0][x - s].set_random_type();
                    }
                    map[i][x - s].sprite.move(0,-100);
                }
            }
            Settings::instance()->set("block_input", 1);
            Settings::instance()->set("in_solve_animation", 1);
            Settings::instance()->set("horizontal_animation", 1);
            Settings::instance()->set("horizontal_check", 0);
        }
        if (Settings::instance()->get_int("vertical_check")) {
            const int x = Settings::instance()->get_int("vertical_x");
            const int y = Settings::instance()->get_int("vertical_y");
            const int count = Settings::instance()->get_int("vertical_count") + 1;
            Settings::instance()->set("update_points", 1);
            Settings::instance()->add("points", (count+(count-3)*(count - 3))*10);

            for (int i = y; i != -1; --i) {
                if (i - count >= 0) {
                    map[i][x].set_type(map[i - count][x].get_type());
                }
                else {
                    map[i][x].set_random_type();
                }
                map[i][x].sprite.move(0,-100*count);
            }

            Settings::instance()->set("block_input", 1);
            Settings::instance()->set("in_solve_animation", 1);
            Settings::instance()->set("vertical_animation", 1);
            Settings::instance()->set("vertical_check", 0);
        }
    }

    void Map::update_solve_animation(const unsigned long long& delta_time) {
        const unsigned long long solve_animation_offset = Settings::instance()->get_ull("solve_animation_offset");
        if(Settings::instance()->get_int("horizontal_animation")){
            const int x = Settings::instance()->get_int("horizontal_x");
            const int y = Settings::instance()->get_int("horizontal_y");
            const unsigned count = Settings::instance()->get_int("horizontal_count");

            if (map[y][x].get_sprite_position() == sf::Vector2f(x_offset + x * 100, y_offset + y * 100)){
                Settings::instance()->set("block_input", 0);
                Settings::instance()->set("in_solve_animation", 0);
                Settings::instance()->set("horizontal_animation", 0);
                solve_time_offset = 0;
                return;
            }
            if (solve_time_offset > solve_animation_offset) {
                for (int i = y; i != -1; --i) {
                    for (int s = 0; s <= count; ++s) {
                        map[i][x - s].sprite.move(0, 10);
                    }
                }
                solve_time_offset %= solve_animation_offset;
            }
            solve_time_offset += delta_time;
        }
        if(Settings::instance()->get_int("vertical_animation")){
            const int x = Settings::instance()->get_int("vertical_x");
            const int y = Settings::instance()->get_int("vertical_y");
            const int count = Settings::instance()->get_int("vertical_count") + 1;

            if (map[y][x].get_sprite_position() == sf::Vector2f(x_offset + x * 100, y_offset + y * 100)) {
                Settings::instance()->set("block_input", 0);
                Settings::instance()->set("in_solve_animation", 0);
                Settings::instance()->set("vertical_animation", 0);
                solve_time_offset = 0;
                return;
            }
            if (solve_time_offset > solve_animation_offset) {
                for (int i = y; i != -1; --i) {
                    map[i][x].sprite.move(0, 10);
                }
                solve_time_offset %= solve_animation_offset;
            }
            solve_time_offset += delta_time;
        }
    }

}
