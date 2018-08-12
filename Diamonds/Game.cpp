#include "stdafx.h"
#include "Game.h"

namespace di
{

    Game::Game()
        :window(sf::VideoMode(1280, 720), "Diamonds"){
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
    }

    void Game::events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

}