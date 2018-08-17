#include "stdafx.h"
#include "Game.h"
#include "Animation.h"
#include "Animated_sprite.h"
#include <SFML/Graphics.hpp>
#include "Animation_manager.h"
#include <iostream>

namespace di
{

    Game::Game()
        :window(sf::VideoMode(800,800), "Diamonds", sf::Style::Close), map(8,8)
    {
        window.setFramerateLimit(60);
        using namespace std::chrono;
        last_frame_time = high_resolution_clock::now();
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();

        mouse_image.loadFromFile("data/textures/mouse.png");
        cursor.loadFromPixels(mouse_image.getPixelsPtr(), mouse_image.getSize(), sf::Vector2u(2, 2));
        window.setMouseCursor(cursor);

        Settings::instance()->set("update_time", "700000");
        Settings::instance()->set("swap_animation_offset", "2500");
    }

    void Game::prepare() {
        for (int i = 1; i != 7; ++i) {
            di::Animation_manager::instance()->get(std::to_string(i) + "_s.png")->set_sheet(di::Texture_manager::instance()->get(std::to_string(i) + "_s.png"));
            di::Animation_manager::instance()->get(std::to_string(i) + "_s.png")->generate_frames_from_line(sf::Vector2u(100, 100));
        }

        map.init();
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

        window.display();
    }

    void Game::update() {
        using namespace std::chrono;
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();
        last_frame_time = high_resolution_clock::now();

        map.update(delta_time, mouse->getPosition(window));
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
