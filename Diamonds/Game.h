#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Texture_manager.h"
#include "Settings.h"
#include "Fps_counter.h"

namespace di
{

    class Game
    {
    public:
        Game();
        ~Game();
        void play();
        void prepare();
    private:
        void draw();
        void update();
        void events();

        di::Fps_counter fps;

        sf::RenderWindow window;
        sf::Mouse mouse;
        sf::Cursor cursor;

        std::chrono::time_point<std::chrono::steady_clock> last_frame_time;
        double delta_time;

    };

}