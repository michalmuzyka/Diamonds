#include "stdafx.h"
#include "Game.h"
#include "Animation.h"
#include "Animated_sprite.h"
#include <SFML/Graphics.hpp>

namespace di
{

    Game::Game()
        :window(sf::VideoMode(1280, 720), "Diamonds"), s1(sf::seconds(0.1).asMicroseconds(), false, true){
        window.setFramerateLimit(60);
        using namespace std::chrono;
        last_frame_time = high_resolution_clock::now();
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();
    }

    Game::~Game(){

    }

    void Game::prepare() {
        anim.set_sheet(di::Texture_manager::instance()->get("2.png"));
        anim.add_frame(sf::IntRect(0, 0, 32, 32));
        anim.add_frame(sf::IntRect(32, 0, 32, 32));
        anim.add_frame(sf::IntRect(64, 0, 32, 32));
        anim.add_frame(sf::IntRect(96, 0, 32, 32));
        s1.set_animation(std::make_shared<Animation>(anim));
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
        window.clear(sf::Color::Red);

        window.draw(fps);
        window.draw(s1);

        window.display();
    }

    void Game::update() {
        fps.update();

        using namespace std::chrono;
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();
        last_frame_time = high_resolution_clock::now();

        s1.update(delta_time);
    }

    void Game::events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

}
