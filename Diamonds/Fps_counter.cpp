#include "stdafx.h"
#include "Fps_counter.h"
#include "Font_manager.h"

namespace di
{

    Fps_counter::Fps_counter()
        :frame(0), fps(0), old_time(std::chrono::high_resolution_clock::now()){
        text.setFont(*di::Font_manager::instance()->get("neon2.ttf"));
        text.setCharacterSize(60); 
        text.setFillColor(sf::Color::Blue);
    }

    unsigned Fps_counter::get_FPS() const {
        return fps;
    }

    void Fps_counter::update() {
        if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()-old_time).count() >= 1.0f){
            fps = frame;
            text.setString(std::to_string(get_FPS()));
            frame = 0;
            old_time = std::chrono::high_resolution_clock::now();
        }
        ++frame;
    }

    void Fps_counter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(text);
    }

}
