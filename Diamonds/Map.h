#pragma once
#include <vector>
#include "Tile.h"

namespace di
{

    class Map :public sf::Drawable
    {
    public:
        Map();

        void init(const unsigned x, const unsigned y);
        void update(const unsigned long long&delta_time, const sf::Vector2i& mouse_pos);
    private:
        unsigned x, y;
        sf::Vector2f tile_size;
        std::vector<std::vector<Tile>> map;
        unsigned long long swap_time_offset, solve_time_offset;
        unsigned x_offset, y_offset;

        bool check_map();
        void make_map_without_completed_puzzle();
        void prepare_swap_animation();
        void prepare_solve_animation();
        void update_swap_animation(const unsigned long long&delta_time);
        void update_solve_animation(const unsigned long long&delta_time);

        bool horizontal_solve = false;
        int horizontal_x=0, horizontal_y = 0, horizontal_count=0;
        bool vertical_solve = false;
        int vertical_x = 0, vertical_y = 0, vertical_count = 0;
        bool is_in_solve_animation = false;
        bool is_in_horizontal_animation = false;
        bool is_in_vertical_animation = false;
        bool is_in_swap_animation = false;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
