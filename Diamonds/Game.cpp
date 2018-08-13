#include "stdafx.h"
#include "Game.h"

namespace di
{

    Game::Game()
        :window(sf::VideoMode(1280, 720), "Diamonds"){
        using namespace std::chrono;
        last_frame_time = high_resolution_clock::now();
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();
    }

    Game::~Game(){

    }

    void Game::prepare() {

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

        window.display();
    }

    void Game::update() {
        fps.update();

        using namespace std::chrono;
        delta_time = duration_cast<microseconds>(high_resolution_clock::now() - last_frame_time).count();
        last_frame_time = high_resolution_clock::now();
    }

    void Game::events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

}