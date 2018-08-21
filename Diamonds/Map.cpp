#include "Map.h"
#include "Settings.h"
#include "Random_int.h"

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

        const auto bounds = map[0][0].get_sprite_bounds();
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

        if(is_in_swap_animation){
            update_swap_animation(delta_time);
        }
        
        if (!Settings::instance()->get_int("block_input")) {
            if (check_map()) {
                prepare_solve_animation();
            }
        }
        
        if(is_in_solve_animation){
            update_solve_animation(delta_time);
        }

    }

    bool Map::check_map() {
        
        //horizontal check
        if (!horizontal_solve && !vertical_solve) {
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
                            horizontal_solve = true;
                            horizontal_x = s+offset-1;
                            horizontal_y = i;
                            horizontal_count = counter;
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
                            vertical_solve = true;
                            vertical_x = i;
                            vertical_y = s+offset-1;
                            vertical_count = counter;
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

        is_in_swap_animation = true;
        Settings::instance()->set("block_input", 1);
    }

    void Map::update_swap_animation(const unsigned long long& delta_time) {
        const unsigned long long swap_animation_offset = Settings::instance()->get_ull("swap_animation_offset");
        const int f_x = Settings::instance()->get_int("first_x");
        const int f_y = Settings::instance()->get_int("first_y");
        const int s_x = Settings::instance()->get_int("second_x");
        const int s_y = Settings::instance()->get_int("second_y");

        if (map[f_y][f_x].get_sprite_position() == sf::Vector2f(x_offset + f_x * 100, y_offset + f_y * 100)) {
            is_in_swap_animation = false;
            Settings::instance()->set("block_input", 0);
            swap_time_offset = 0;
        }
        else {
            if (swap_time_offset > swap_animation_offset) {
                map[f_y][f_x].move_sprite((f_x - s_x) * 10, (f_y - s_y) * 10);
                map[s_y][s_x].move_sprite((s_x - f_x) * 10, (s_y - f_y) * 10);
                swap_time_offset %= swap_animation_offset;
            }
            swap_time_offset += delta_time;
        }
    }

    void Map::prepare_solve_animation() {
        if (horizontal_solve) {
            Settings::instance()->set("update_points", 1);
            Settings::instance()->add("points", (horizontal_count +1 + (horizontal_count -2)*(horizontal_count - 2)) * 10);
            for (int i = horizontal_y; i != -1; --i) {
                for (int s = 0; s <= horizontal_count; ++s) {
                    if (i != 0) {
                        map[i][horizontal_x - s].set_type(map[i - 1][horizontal_x - s].get_type());
                    }
                    else {
                        map[0][horizontal_x - s].set_random_type();
                    }
                    map[i][horizontal_x - s].move_sprite(0,-100);
                }
            }
            Settings::instance()->set("block_input", 1);
            is_in_solve_animation = true;
            is_in_horizontal_animation = true;
            horizontal_solve = false;
        }
        if (vertical_solve) {
            vertical_count += 1;
            Settings::instance()->set("update_points", 1);
            Settings::instance()->add("points", (vertical_count +(vertical_count -3)*(vertical_count - 3))*10);

            for (int i = vertical_y; i != -1; --i) {
                if (i - vertical_count >= 0) {
                    map[i][vertical_x].set_type(map[i - vertical_count][vertical_x].get_type());
                }
                else {
                    map[i][vertical_x].set_random_type();
                }
                map[i][vertical_x].move_sprite(0,-100 * vertical_count);
            }

            Settings::instance()->set("block_input", 1);
            is_in_solve_animation = true;
            is_in_vertical_animation = true;
            vertical_solve = false;
        }
    }
    void Map::update_solve_animation(const unsigned long long& delta_time) {
        const unsigned long long solve_animation_offset = Settings::instance()->get_ull("solve_animation_offset");
        if(is_in_horizontal_animation){

            if (map[horizontal_y][horizontal_x].get_sprite_position() == sf::Vector2f(x_offset + horizontal_x * 100, y_offset + horizontal_y * 100)){
                Settings::instance()->set("block_input", 0);
                is_in_solve_animation = false;
                is_in_horizontal_animation = false;
                solve_time_offset = 0;
                return;
            }
            if (solve_time_offset > solve_animation_offset) {
                for (int i = horizontal_y; i != -1; --i) {
                    for (int s = 0; s <= horizontal_count; ++s) {
                        map[i][horizontal_x - s].move_sprite(0, 10);
                    }
                }
                solve_time_offset %= solve_animation_offset;
            }
            solve_time_offset += delta_time;
        }
        if(is_in_vertical_animation){

            if (map[vertical_y][vertical_x].get_sprite_position() == sf::Vector2f(x_offset + vertical_x * 100, y_offset + vertical_y * 100)) {
                Settings::instance()->set("block_input", 0);
                is_in_solve_animation = false;
                is_in_vertical_animation = false;
                solve_time_offset = 0;
                return;
            }
            if (solve_time_offset > solve_animation_offset) {
                for (int i = vertical_y; i != -1; --i) {
                    map[i][vertical_x].move_sprite(0, 10);
                }
                solve_time_offset %= solve_animation_offset;
            }
            solve_time_offset += delta_time;
        }
    }

}
