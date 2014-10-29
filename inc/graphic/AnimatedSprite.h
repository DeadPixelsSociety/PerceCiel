#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "SFML/Graphics.hpp"

class AnimatedSprite: public sf::Sprite{

    public:
        AnimatedSprite(sf::Texture& texture, sf::IntRect firstFrame);
        ~AnimatedSprite();
        void addFrame(const sf::IntRect textureRect);
        void nextFrame();

    private:
        std::vector<sf::IntRect> m_frames;
        unsigned int m_currentFrameIndex;

};

#endif
