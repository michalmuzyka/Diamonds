#pragma once
#include "Animated_sprite.h"
#include <string>


namespace di
{

    class Tile :public sf::Drawable
    {
    public:
        Tile();
        explicit Tile(const unsigned &type);
        void update(const unsigned long long&delta_time);
        Animated_sprite sprite;

    private:
        unsigned type;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
