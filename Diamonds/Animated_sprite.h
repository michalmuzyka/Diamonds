#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.h"

namespace di
{

    class Animated_sprite :public sf::Drawable, public sf::Transformable
    {
    public:
        explicit Animated_sprite(const double &step_time, const bool &paused, const bool &looped);

        void update(const double &delta_time);

        void set_animation(std::shared_ptr<Animation> animation);
        void set_frame(const std::size_t &n);
        void set_loop(const bool &loop);
        void set_step_time(const double &time);
        void pause();
        void play();

        std::shared_ptr<di::Animation> get_animation() const;
        double get_step_time() const;
        bool is_paused() const;
        bool is_looped() const;

    private:
        const std::shared_ptr<di::Animation> animation;
        const std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;

        std::size_t frame_number;
        bool looped;
        bool paused;

        double step_time;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
