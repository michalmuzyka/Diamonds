#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Texture_manager.h"
#include "Settings.h"
#include "Fps_counter.h"
#include "Animated_sprite.h"
#include "Map.h"

namespace di
{

    class Game
    {
    public:
        Game();
        void play();
        void prepare();
    private:
        void draw();
        void update();
        void events();

        sf::RenderWindow window;
        sf::Cursor cursor;
        sf::Image mouse_image;
        std::shared_ptr<sf::Mouse> mouse;

        std::chrono::time_point<std::chrono::steady_clock> last_frame_time;
        unsigned long long delta_time;

        Map map;
    };

}
