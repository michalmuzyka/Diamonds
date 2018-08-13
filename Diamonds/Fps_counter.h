#pragma once
#include <chrono>
#include <SFML/Graphics.hpp>

namespace di
{

    class Fps_counter :public sf::Drawable
    {
    public:
        sf::Text text;
        Fps_counter();
        void update();
        unsigned int get_FPS() const;

    private:
        unsigned int frame;
        unsigned int fps;
        std::chrono::time_point<std::chrono::steady_clock> old_time{};

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
