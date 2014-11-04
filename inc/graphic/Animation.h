#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"
#include <vector>

class Animation{

    public:
        Animation(sf::IntRect firstFrame);
        ~Animation();
        sf::IntRect getCurrentFrame();
        void addFrame(sf::IntRect frame);
        void nextFrame();

    private:
        std::vector<sf::IntRect> m_frames;
        unsigned int m_currentFrameIndex;

};

#endif
