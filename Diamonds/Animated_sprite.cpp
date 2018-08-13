#include "stdafx.h"
#include "Animated_sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace di
{

    Animated_sprite::Animated_sprite(const double& step_time=sf::seconds(0.2).asMicroseconds(), const bool& paused=false, const bool& looped=true)
        :animation(nullptr), texture(nullptr), frame_number(0), looped(looped), paused(paused), step_time(step_time)
    {
        
    }

    void Animated_sprite::update(const double& delta_time) {
        
    }

    void Animated_sprite::play() {
        paused = false;
    }

    bool Animated_sprite::is_looped() const {
        return looped;
    }

    bool Animated_sprite::is_paused() const {
        return paused;
    }

    void Animated_sprite::pause() {
        paused = true;
    }

    std::shared_ptr<di::Animation> Animated_sprite::get_animation() const {
        return animation;
    }

    double Animated_sprite::get_step_time() const {
        return step_time;
    }

    void Animated_sprite::set_animation(std::shared_ptr<Animation> animation) {
        this->animation = animation;
        texture = animation->get_sheet();
        set_frame(0);
    }

    void Animated_sprite::set_frame(const std::size_t& n) {
        sprite.setTextureRect(animation->get_frame(n));
    }

    void Animated_sprite::set_loop(const bool& loop) {
        looped = loop;
    }

    void Animated_sprite::set_step_time(const double& time) {
        step_time = time;
    }

    void Animated_sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (animation&&texture) {
            states.transform *= getTransform();
            states.texture = *texture;
            target.draw(sprite);
        }
    }
}
