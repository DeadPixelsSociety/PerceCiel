#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "SFML/Graphics.hpp"
#include "graphic/Animation.h"

class AnimatedSprite: public sf::Sprite{

    public:
        AnimatedSprite(sf::Texture& texture);
        ~AnimatedSprite();
        void addAnimation(int key, Animation& animation);
        void nextFrame();
        void selectAnimation(int key);

    private:
        Animation* m_currentAnimation;
        std::map<int, Animation*> m_animations;

};

#endif
