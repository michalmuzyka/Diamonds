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

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
