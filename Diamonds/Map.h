#pragma once
#include <vector>
#include "Tile.h"

namespace di
{

    class Map :public sf::Drawable
    {
    public:
        Map(const unsigned x, const unsigned y);

        void init();
        void update(const unsigned long long&delta_time, const sf::Vector2i& mouse_pos);
    private:
        unsigned x, y;
        sf::Vector2f tile_size;
        std::vector<std::vector<Tile>> map;
        unsigned long long swap_time_offset;
        bool check_map();
        void make_map_without_completed_puzzle();
        void prepare_swap_animation();
        void prepare_solve_animation();
        void update_swap_animation(const unsigned long long&delta_time);
        void update_solve_animation(const unsigned long long&delta_time);
        

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
