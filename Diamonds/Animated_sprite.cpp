#include "stdafx.h"
#include "Animated_sprite.h"

namespace di
{

    Animated_sprite::Animated_sprite(const unsigned long long& step_time, const bool& paused, const bool& looped)
        :animation(nullptr), texture(nullptr), frame_number(0), looped(looped), paused(paused), step_time(step_time), current_time(0), ended(0)
    {
        
    }

    void Animated_sprite::update(const unsigned long long& delta_time) {
        if(!paused && animation){
            current_time += delta_time;
            if(delta_time+current_time >= step_time){
                current_time = (delta_time + current_time) % step_time;

                if (frame_number + 1 < animation->get_animation_length())
                    ++frame_number;
                else {
                    frame_number = 0;

                    if (!looped) {
                        ended = true;
                        paused = true;
                    }
                }
                set_frame(frame_number);
            }
        }
    }

    void Animated_sprite::play() {
        paused = false;
        ended = false;
    }

    bool Animated_sprite::is_looped() const {
        return looped;
    }

    bool Animated_sprite::is_paused() const {
        return paused;
    }

    bool Animated_sprite::is_ended() const {
        return ended;
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
        sprite.setTexture(*texture);
        set_frame(0);
    }

    void Animated_sprite::set_frame(const std::size_t& n) {
        sprite.setTextureRect(animation->get_frame(n));
    }

    void Animated_sprite::set_loop(const bool& loop) {
        looped = loop;
    }

    void Animated_sprite::set_step_time(const unsigned long long& time) {
        step_time = time;
    }


    sf::FloatRect Animated_sprite::getBounds() const {
        const auto bounds = sprite.getGlobalBounds();
        const auto pos = getPosition();
        return sf::FloatRect(pos.x, pos.y, bounds.width, bounds.height);
    }


    void Animated_sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (animation&&texture) {
            states.transform *= getTransform();
            target.draw(sprite, states);
        }
    }
}
