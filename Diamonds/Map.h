#pragma once
#include <vector>
#include "Tile.h"

namespace di
{

    class Map :public sf::Drawable
    {
    public:
        Map(const unsigned x, const unsigned y);

        void scale(const float x,const float y);
        void init();
        void update(const unsigned long long&delta_time);
    private:
        unsigned x, y;
        sf::Vector2f tile_size;
        std::vector<std::vector<Tile>> map;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
