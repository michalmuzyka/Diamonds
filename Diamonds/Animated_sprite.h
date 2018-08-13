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
        Animated_sprite();
        ~Animated_sprite();
    private:
        std::shared_ptr<di::Animation> animation;
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;

    };

}
