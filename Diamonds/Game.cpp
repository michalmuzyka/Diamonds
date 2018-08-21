#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Animation.h"
#include "Animated_sprite.h"
#include "Animation_manager.h"

namespace di
{

    Game::Game()
        :window(sf::VideoMode::getDesktopMode(), "Diamonds", sf::Style::Fullscreen)
    {
        const auto video_mode = window.getSize();
        Settings::instance()->set("screen_width", video_mode.x);
        Settings::instance()->set("screen_height", video_mode.y);

        window.setFramerateLimit(60);

        using namespace std::chrono;
        last_frame_time = high_resolution_clock::now();
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();

        mouse_image.loadFromFile("data/textures/mouse.png");
        cursor.loadFromPixels(mouse_image.getPixelsPtr(), mouse_image.getSize(), sf::Vector2u(2, 2));
        window.setMouseCursor(cursor);

        sf::Image icon;
        icon.loadFromFile("data/textures/icon.png");
        window.setIcon(64, 64, icon.getPixelsPtr());

        Settings::instance()->set("update_time", 1300000);
        Settings::instance()->set("swap_animation_offset", 2500);
        Settings::instance()->set("solve_animation_offset", 2500);
    }

    void Game::prepare() {
        for (int i = 1; i != 7; ++i) {
            Animation_manager::instance()->get(std::to_string(i) + "_s.png")->set_sheet(di::Texture_manager::instance()->get(std::to_string(i) + "_s.png"));
            Animation_manager::instance()->get(std::to_string(i) + "_s.png")->generate_frames_from_line(sf::Vector2u(100, 100));
        }

        const unsigned count_of_tiles = Settings::instance()->get_int("screen_height") / 100;
        map.init(count_of_tiles, count_of_tiles);

        const unsigned y_offset = Settings::instance()->get_int("y_offset");
        text_points.setString("Points:");
        text_points.setPosition(20, y_offset);
        text_points.setFillColor(sf::Color(255, 93, 13));
        text_points.setCharacterSize(50);
        text_points.setFont(*Font_manager::instance()->get("neon2.ttf"));

        text_count_points.setFont(*Font_manager::instance()->get("neon2.ttf"));
        text_count_points.setPosition(20, y_offset+50);
        text_count_points.setFillColor(sf::Color(255, 93, 13));
        text_count_points.setCharacterSize(50);
        text_count_points.setString("0");
    }

    void Game::play() {
        while (window.isOpen()) {
            events();
            update();
            draw();
        }
    }

    void Game::draw() {
        window.clear(sf::Color(255, 239, 220));

        window.draw(map);
        window.draw(text_points);
        window.draw(text_count_points);

        window.display();
    }

    void Game::update() {
        using namespace std::chrono;
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();
        last_frame_time = high_resolution_clock::now();

        map.update(delta_time, mouse->getPosition(window));
        fps.update();

        if(Settings::instance()->get_int("update_points")){
            text_count_points.setString(Settings::instance()->get_string("points"));
            Settings::instance()->set("update_points", 0);
        }
    }

    void Game::events() {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch(event.type){
            case sf::Event::Closed: {
                window.close();
                break;
            }
            case sf::Event::KeyPressed: {
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }
            default: break;
            }
        }
    }

}
