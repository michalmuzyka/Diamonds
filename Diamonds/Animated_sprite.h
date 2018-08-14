#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace di
{

    class Animated_sprite :public sf::Drawable, public sf::Transformable
    {
    public:
        explicit Animated_sprite(const unsigned long long &step_time= sf::seconds(0.2).asMicroseconds(), const bool &paused=false, const bool &looped=true);

        void update(const unsigned long long&delta_time);

        void set_animation(std::shared_ptr<Animation> animation);
        void set_frame(const std::size_t &n);
        void set_loop(const bool &loop);
        void set_step_time(const unsigned long long &time);
        void pause();
        void play();

        sf::FloatRect getLocalBounds() const;

        std::shared_ptr<di::Animation> get_animation() const;
        double get_step_time() const;
        bool is_paused() const;
        bool is_looped() const;

    private:
        std::shared_ptr<di::Animation> animation;
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;

        std::size_t frame_number;
        bool looped;
        bool paused;

        unsigned long long step_time;
        unsigned long long current_time;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
