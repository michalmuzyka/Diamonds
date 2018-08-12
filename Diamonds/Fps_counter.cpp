#include "stdafx.h"
#include "Fps_counter.h"
#include "Font_manager.h"

namespace di
{

    Fps_counter::Fps_counter()
        : mFrame(0), mFps(0), oldTime(std::chrono::high_resolution_clock::now()){

        text.setFont(*di::Font_manager::instance()->get_default());
        text.setFillColor(sf::Color::Black);
    }

    const unsigned Fps_counter::getFPS() const {
        return mFps;
    }

    void Fps_counter::update() {
        if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()-oldTime).count() >= 1.0f){
            mFps = mFrame;
            text.setString(std::to_string(getFPS()));
            mFrame = 0;
            oldTime = std::chrono::high_resolution_clock::now();
        }
        ++mFrame;
    }

    void Fps_counter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(text);
    }

}
