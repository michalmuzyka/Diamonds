#include "stdafx.h"
#include "Game.h"
#include "Animation.h"
#include "Animated_sprite.h"
#include <SFML/Graphics.hpp>
#include "Animation_manager.h"

namespace di
{

    Game::Game()
        :window(sf::VideoMode(1920, 1080), "Diamonds"), s1(sf::seconds(0.15).asMicroseconds(), false, true)
    {
        window.setFramerateLimit(60);
        using namespace std::chrono;
        last_frame_time = high_resolution_clock::now();
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();
    }

    Game::~Game(){

    }

    void Game::prepare() {
        di::Animation_manager::instance()->get("a1")->set_sheet(di::Texture_manager::instance()->get("2_s.png"));
        di::Animation_manager::instance()->get("a1")->generate_frames_from_line(sf::Vector2u(100,100));
        s1.set_animation(di::Animation_manager::instance()->get("a1"));

        /*
        s2.set_animation(std::make_shared<Animation>(anim1));
        s3.set_animation(std::make_shared<Animation>(anim2));
        s3.move(228, 100);
        s2.move(164, 100);
        */
        s1.scale(0.5, 0.5);
        s1.move(100, 100);
    }

    void Game::play() {
        while (window.isOpen()) {
            events();
            update();
            draw();
        }
    }

    void Game::draw() {
        window.clear(sf::Color::White);

        window.draw(fps);
        window.draw(s1);
        window.draw(s2);
        window.draw(s3);

        window.display();
    }

    void Game::update() {
        fps.update();

        using namespace std::chrono;
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();
        last_frame_time = high_resolution_clock::now();

        s1.update(delta_time);
        s2.update(delta_time);
        s3.update(delta_time);
    }

    void Game::events() {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch(event.type){
            case sf::Event::Closed: {
                window.close();
                break;
            }
            default: break;
            }
        }
    }

}
