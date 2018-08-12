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
        const unsigned int getFPS() const;

    private:
        unsigned int mFrame;
        unsigned int mFps;
        std::chrono::time_point<std::chrono::steady_clock> oldTime;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
